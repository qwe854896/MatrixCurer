#include "matrix_curer/MatrixOperation.hpp"

#include <stdexcept>

Matrix MatrixOperation::transpose(const Matrix &A)
{
    const size_t m = A.nrow();
    const size_t n = A.ncol();
    Matrix result(n, m);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            result(i, j) = A(j, i);
        }
    }
    return result;
}

Matrix MatrixOperation::inverse(const Matrix &A)
{
    if (A.nrow() != A.ncol())
    {
        throw std::invalid_argument("MatrixOperation::inverse - Input matrix must be square");
    }

    size_t n = A.nrow();
    Matrix augmented(n, n << 1);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            augmented(i, j) = A(i, j);
    for (int i = 0; i < n; ++i)
        augmented(i, n + i) = 1.0;

    // Gaussian elimination with partial pivoting
    for (size_t i = 0; i < n; ++i)
    {
        size_t maxRow = i;
        double maxValue = std::abs(augmented(i, i));
        for (size_t j = i + 1; j < n; ++j)
        {
            double value = std::abs(augmented(j, i));
            if (value > maxValue)
            {
                maxRow = j;
                maxValue = value;
            }
        }
        if (maxValue == 0.0)
        {
            throw std::runtime_error("MatrixOperation::inverse - Matrix is singular");
        }
        if (maxRow != i)
        {
            for (int j = (n << 1) - 1; j >= 0; --j)
                std::swap(augmented(i, j), augmented(maxRow, j));
        }

        double pivot = augmented(i, i);
        for (size_t j = i; j < 2 * n; ++j)
        {
            augmented(i, j) /= pivot;
        }

        for (size_t k = 0; k < n; ++k)
        {
            if (k != i)
            {
                double factor = augmented(k, i);
                for (size_t j = i; j < 2 * n; ++j)
                {
                    augmented(k, j) -= factor * augmented(i, j);
                }
            }
        }
    }

    Matrix inverse(n, n);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            inverse(i, j) = augmented(i, j + n);
        }
    }

    return inverse;
}

bool MatrixOperation::is_symmetric(const Matrix &A)
{
    if (A.nrow() != A.ncol())
    {
        return false;
    }
    for (size_t i = 0; i < A.nrow(); ++i)
    {
        for (size_t j = 0; j <= i; ++j)
        {
            if (A(i, j) != A(j, i))
            {
                return false;
            }
        }
    }
    return true;
}

Matrix MatrixOperation::Identity(const size_t &size)
{
    Matrix mat(size, size);
    for (int i = 0; i < size; ++i)
        mat(i, i) = 1;
    return mat;
}

void MatrixOperation::set_identity(Matrix &A)
{
    const size_t n = A.nrow();
    resize(A, n, n);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            A(i, j) = (i == j) ? 1.0 : 0.0;
        }
    }
}

void MatrixOperation::resize(Matrix &A, const size_t &row, const size_t &col)
{
    A.buffer().resize(row * col);
    A.m_nrow = row;
    A.m_ncol = col;
}