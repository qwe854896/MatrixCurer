#include "matrix_curer/Matrix.hpp"

#include <stdexcept>
#include <cstring>

// Default constructor
Matrix::Matrix() : m_nrow(0), m_ncol(0), m_buffer() {}

// Copy constructor
Matrix::Matrix(const Matrix &other)
    : m_nrow(other.m_nrow), m_ncol(other.m_ncol), m_buffer(other.m_buffer) {}

// Move constructor
Matrix::Matrix(Matrix &&other) noexcept
    : m_nrow(other.m_nrow), m_ncol(other.m_ncol), m_buffer(std::move(other.m_buffer)) {}

// Custom constructor
Matrix::Matrix(const size_t &row, const size_t &col)
    : m_nrow(row), m_ncol(col), m_buffer(row * col, 0.0) {}

// Copy assignment operator
Matrix &Matrix::operator=(const Matrix &other)
{
    if (this != &other)
    {
        m_nrow = other.m_nrow;
        m_ncol = other.m_ncol;
        std::copy(other.m_buffer.begin(), other.m_buffer.end(), m_buffer.begin());
    }
    return *this;
}

// Move assignment operator
Matrix &Matrix::operator=(Matrix &&other) noexcept
{
    if (this != &other)
    {
        m_nrow = other.m_nrow;
        m_ncol = other.m_ncol;
        m_buffer = std::move(other.m_buffer);
    }
    return *this;
}

// Destructor
Matrix::~Matrix() {}

// No bound check.
// Element access functions
double Matrix::operator()(const size_t &row, const size_t &col) const
{
    return m_buffer[row * m_ncol + col];
}

double &Matrix::operator()(const size_t &row, const size_t &col)
{
    return m_buffer[row * m_ncol + col];
}

// Size functions
size_t Matrix::nrow() const
{
    return m_nrow;
}

size_t Matrix::ncol() const
{
    return m_ncol;
}

// Buffer functions
std::vector<double, CustomAllocator<double>> &Matrix::buffer()
{
    return m_buffer;
}

const std::vector<double, CustomAllocator<double>> &Matrix::buffer() const
{
    return m_buffer;
}

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

// Arithmetic operators
Matrix Matrix::operator+(const Matrix &other) const
{
    if (m_nrow != other.m_nrow || m_ncol != other.m_ncol)
    {
        throw std::runtime_error("Matrix dimensions are not compatible for addition.");
    }

    Matrix result(m_nrow, m_ncol);
    for (size_t i = 0; i < m_nrow; i++)
    {
        for (size_t j = 0; j < m_ncol; j++)
        {
            result(i, j) = (*this)(i, j) + other(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix &other) const
{
    if (m_nrow != other.m_nrow || m_ncol != other.m_ncol)
    {
        throw std::runtime_error("Matrix dimensions are not compatible for subtraction.");
    }

    Matrix result(m_nrow, m_ncol);
    for (size_t i = 0; i < m_nrow; i++)
    {
        for (size_t j = 0; j < m_ncol; j++)
        {
            result(i, j) = (*this)(i, j) - other(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &other) const
{
    if (m_ncol != other.m_nrow)
    {
        throw std::runtime_error("Matrix dimensions are not compatible for multiplication.");
    }

    size_t resultRows = m_nrow;
    size_t resultCols = other.m_ncol;
    size_t commonDim = m_ncol;

    Matrix result(resultRows, resultCols);
    for (size_t i = 0; i < resultRows; i++)
    {
        for (size_t j = 0; j < resultCols; j++)
        {
            double sum = 0.0;
            for (size_t k = 0; k < commonDim; k++)
            {
                sum += (*this)(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}

// Unary negation operator
Matrix Matrix::operator-() const
{
    Matrix result(m_nrow, m_ncol);
    for (size_t i = 0; i < m_nrow; i++)
    {
        for (size_t j = 0; j < m_ncol; j++)
        {
            result(i, j) = -(*this)(i, j);
        }
    }
    return result;
}
