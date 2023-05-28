#include <stdexcept>
#include <utility>
#include <cmath>

#include "MatrixCurer/Matrix.h"

// Default constructor
Matrix::Matrix()
    : m_nrow(0), m_ncol(0)
{
}

// Copy constructor
Matrix::Matrix(const Matrix &other)
    : m_nrow(other.m_nrow), m_ncol(other.m_ncol), m_buffer(other.m_buffer)
{
}

// Move constructor
Matrix::Matrix(Matrix &&other) noexcept
    : m_nrow(std::exchange(other.m_nrow, 0)),
      m_ncol(std::exchange(other.m_ncol, 0)),
      m_buffer(std::move(other.m_buffer))
{
}

// Custom constructor
Matrix::Matrix(const size_t &nrow, const size_t &ncol)
    : m_nrow(nrow), m_ncol(ncol), m_buffer(nrow * ncol, 0.0)
{
}

// Copy assignment operator
Matrix &Matrix::operator=(const Matrix &other)
{
    if (this != &other)
    {
        m_nrow = other.m_nrow;
        m_ncol = other.m_ncol;
        m_buffer = other.m_buffer;
    }
    return *this;
}

// Move assignment operator
Matrix &Matrix::operator=(Matrix &&other) noexcept
{
    m_nrow = std::exchange(other.m_nrow, 0);
    m_ncol = std::exchange(other.m_ncol, 0);
    m_buffer = std::move(other.m_buffer);
    return *this;
}

// Destructor
Matrix::~Matrix()
{
    m_buffer.clear();
}

// No bound check.
double Matrix::operator()(const size_t &row, const size_t &col) const
{
    return m_buffer[row * m_ncol + col];
}
double &Matrix::operator()(const size_t &row, const size_t &col)
{
    return m_buffer[row * m_ncol + col];
}

size_t Matrix::nrow() const { return m_nrow; }
size_t Matrix::ncol() const { return m_ncol; }
std::vector<double> &Matrix::buffer() { return m_buffer; }
const std::vector<double> &Matrix::buffer() const { return m_buffer; }

bool Matrix::operator==(const Matrix &other) const
{
    if (nrow() != other.nrow() || ncol() != other.ncol())
        return false;
    for (size_t i = 0; i < nrow(); ++i)
        for (size_t j = 0; j < ncol(); ++j)
            if (operator()(i, j) != other(i, j))
                return false;
    return true;
}
bool Matrix::operator!=(const Matrix &other) const
{
    return !(*this == other);
}

Matrix Matrix::transpose() const
{
    const size_t m = nrow();
    const size_t n = ncol();
    Matrix result(n, m);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            result(i, j) = (*this)(j, i);
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &other) const
{
    const size_t m = nrow();
    const size_t n = ncol();
    const size_t p = other.ncol();

    if (n != other.nrow())
    {
        throw std::invalid_argument("Matrix::operator*: sizes do not match");
    }

    Matrix result(m, p);

    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < p; ++j)
        {
            double sum = 0.0;
            for (size_t k = 0; k < n; ++k)
            {
                sum += (*this)(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }

    return result;
}

void Matrix::svd(Matrix &U, Matrix &S, Matrix &Vt) const
{
    const size_t m = nrow();
    const size_t n = ncol();

    // Compute A^T * A
    Matrix AtA(n, n);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = i; j < n; ++j)
        {
            double sum = 0.0;
            for (size_t k = 0; k < m; ++k)
            {
                sum += (*this)(k, i) * (*this)(k, j);
            }
            AtA(i, j) = sum;
            AtA(j, i) = sum;
        }
    }

    // Compute eigenvalue decomposition of A^T * A
    Matrix eigen_vectors(n, n);
    Matrix eigen_values(n, 1);
    AtA.eigen_symmetric(eigen_values, eigen_vectors);

    // Compute V
    Vt = eigen_vectors.transpose();

    // Compute A * V
    Matrix Av(m, n);
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            double sum = 0.0;
            for (size_t k = 0; k < n; ++k)
            {
                sum += (*this)(i, k) * Vt(j, k);
            }
            Av(i, j) = sum;
        }
    }

    // Compute S
    S = Matrix(n, n);
    for (size_t i = 0; i < n; ++i)
    {
        S(i, i) = std::sqrt(std::max(eigen_values(i, 0), 0.0));
    }

    // Compute U
    U = Matrix(m, n);
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            U(i, j) = Av(i, j) / S(j, j);
        }
    }
}

void Matrix::eigen_symmetric(Matrix &eigen_values, Matrix &eigen_vectors) const
{
    // Check that the matrix is symmetric
    if (!is_symmetric())
    {
        throw std::invalid_argument("Matrix::eigen_symmetric: matrix is not symmetric");
    }

    // Initialize eigenvalues and eigenvectors
    const size_t n = nrow();
    eigen_values.resize(n, 1);
    eigen_vectors.resize(n, n);
    eigen_vectors.set_identity();

    // Define tolerance and maximum number of iterations
    const double tol = 1e-10;
    const int max_iterations = 1000;

    // Create a copy of the input matrix to store the result
    Matrix A(*this);

    // Loop until off-diagonal elements are small enough
    for (int iteration = 0; iteration < max_iterations; ++iteration)
    {
        // Find the largest off-diagonal element
        double max_off_diag = 0.0;
        size_t max_i = 0, max_j = 0;
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = i + 1; j < n; ++j)
            {
                double off_diag = std::abs(A(i, j));
                if (off_diag > max_off_diag)
                {
                    max_off_diag = off_diag;
                    max_i = i;
                    max_j = j;
                }
            }
        }

        // Check if off-diagonal elements are small enough
        if (max_off_diag < tol)
        {
            break;
        }

        // Compute the rotation angle
        double theta = 0.5 * std::atan2(2.0 * A(max_i, max_j), A(max_i, max_i) - A(max_j, max_j));

        // Compute the rotation matrix
        Matrix R(n, n);
        R.set_identity();
        R(max_i, max_i) = std::cos(theta);
        R(max_j, max_j) = std::cos(theta);
        R(max_i, max_j) = -std::sin(theta);
        R(max_j, max_i) = std::sin(theta);

        // Update the matrix and eigenvectors
        A = R.transpose() * A * R;
        eigen_vectors = eigen_vectors * R;

        // Check for convergence
        double sum_off_diag = 0.0;
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = i + 1; j < n; ++j)
            {
                sum_off_diag += std::abs(A(i, j));
            }
        }
        if (sum_off_diag < tol)
        {
            break;
        }
    }

    // Extract eigenvalues from diagonal of matrix
    for (size_t i = 0; i < n; ++i)
    {
        eigen_values(i, 0) = A(i, i);
    }

    // Normalize eigenvectors
    for (size_t i = 0; i < n; ++i)
    {
        // Calculate the length of the i-th eigenvector
        double norm = 0.0;
        for (size_t j = 0; j < n; ++j)
        {
            norm += std::pow(eigen_vectors(j, i), 2);
        }
        norm = std::sqrt(norm);
        // Normalize the i-th eigenvector
        for (size_t j = 0; j < n; ++j)
        {
            eigen_vectors(j, i) /= norm;
        }
    }
}

bool Matrix::is_symmetric() const
{
    if (nrow() != ncol())
    {
        return false;
    }
    for (size_t i = 0; i < nrow(); ++i)
    {
        for (size_t j = 0; j <= i; ++j)
        {
            if ((*this)(i, j) != (*this)(j, i))
            {
                return false;
            }
        }
    }
    return true;
}

void Matrix::set_identity()
{
    const size_t n = nrow();
    resize(n, n);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            (*this)(i, j) = (i == j) ? 1.0 : 0.0;
        }
    }
}

void Matrix::resize(const size_t &row, const size_t &col)
{
    m_buffer.resize(row * col);
    m_nrow = row;
    m_ncol = col;
}