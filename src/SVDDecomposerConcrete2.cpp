
#include "matrix_curer/SVDDecomposerConcrete2.hpp"

#include <cmath>
#include <stdexcept>

#include "matrix_curer/MatrixOperation.hpp"

namespace
{
    void eigen_symmetric(const Matrix &_A, Matrix &eigen_values, Matrix &eigen_vectors)
    {
        // Check that the matrix is symmetric
        if (!MatrixOperation::is_symmetric(_A))
        {
            throw std::invalid_argument("Matrix::eigen_symmetric: matrix is not symmetric");
        }

        // Initialize eigenvalues and eigenvectors
        const size_t n = _A.nrow();
        MatrixOperation::resize(eigen_values, n, 1);
        MatrixOperation::resize(eigen_vectors, n, n);
        MatrixOperation::set_identity(eigen_vectors);

        // Define tolerance and maximum number of iterations
        const long double tol = 1e-10;
        const int max_iterations = 1000;

        // Create a copy of the input matrix to store the result
        Matrix A(_A);

        // Loop until off-diagonal elements are small enough
        for (int iteration = 0; iteration < max_iterations; ++iteration)
        {
            // Find the largest off-diagonal element
            long double max_off_diag = 0.0;
            size_t max_i = 0, max_j = 0;
            for (size_t i = 0; i < n; ++i)
            {
                for (size_t j = i + 1; j < n; ++j)
                {
                    long double off_diag = std::abs(A(i, j));
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
            long double theta = 0.5 * std::atan2(2.0 * A(max_i, max_j), A(max_i, max_i) - A(max_j, max_j));

            // Compute the rotation matrix
            Matrix R(n, n);
            MatrixOperation::set_identity(R);
            R(max_i, max_i) = std::cos(theta);
            R(max_j, max_j) = std::cos(theta);
            R(max_i, max_j) = -std::sin(theta);
            R(max_j, max_i) = std::sin(theta);

            // Update the matrix and eigenvectors
            A = MatrixOperation::transpose(R) * A * R;
            eigen_vectors = eigen_vectors * R;

            // Check for convergence
            long double sum_off_diag = 0.0;
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
            long double norm = 0.0;
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
}

void SVDDecomposerConcrete2::decompose(const Matrix &A, Matrix &U, Matrix &S, Matrix &Vt)
{
    const size_t m = A.nrow();
    const size_t n = A.ncol();

    // Compute A^T * A
    Matrix AtA(n, n);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = i; j < n; ++j)
        {
            long double sum = 0.0;
            for (size_t k = 0; k < m; ++k)
            {
                sum += A(k, i) * A(k, j);
            }
            AtA(i, j) = sum;
            AtA(j, i) = sum;
        }
    }

    // Compute eigenvalue decomposition of A^T * A
    Matrix eigen_vectors(n, n);
    Matrix eigen_values(n, 1);
    eigen_symmetric(AtA, eigen_values, eigen_vectors);

    // Compute V
    Vt = MatrixOperation::transpose(eigen_vectors);

    // Compute A * V
    Matrix Av(m, n);
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            long double sum = 0.0;
            for (size_t k = 0; k < n; ++k)
            {
                sum += A(i, k) * Vt(j, k);
            }
            Av(i, j) = sum;
        }
    }

    // Compute S
    S = Matrix(n, n);
    for (size_t i = 0; i < n; ++i)
    {
        S(i, i) = std::sqrt(std::max(eigen_values(i, 0), (double)0.0));
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
