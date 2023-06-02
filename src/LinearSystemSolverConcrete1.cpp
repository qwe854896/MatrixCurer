#include "matrix_curer/LinearSystemSolverConcrete1.hpp"
#include "matrix_curer/utils.hpp"

void LinearSystemSolverConcrete1::solve(const Matrix &_A, const Matrix &_b, Matrix &x)
{
    Matrix A(_A), b(_b);

    const size_t n = A.nrow();
    const size_t m = A.ncol();

    if (n != m)
    {
        throw std::invalid_argument("GaussianElimination: A is not square");
    }

    if (b.nrow() != n || b.ncol() != 1)
    {
        throw std::invalid_argument("GaussianElimination: b has wrong size");
    }

    // Forward elimination
    for (size_t k = 0; k < n - 1; ++k)
    {
        // Find the pivot row
        size_t pivot_row = k;
        long double pivot_value = std::abs(A(k, k));
        for (size_t i = k + 1; i < n; ++i)
        {
            long double abs_value = std::abs(A(i, k));
            if (abs_value > pivot_value)
            {
                pivot_row = i;
                pivot_value = abs_value;
            }
        }

        // Swap pivot row with current row if needed
        if (pivot_row != k)
        {
            for (size_t j = 0; j < m; ++j)
            {
                std::swap(A(k, j), A(pivot_row, j));
            }
            std::swap(b(k, 0), b(pivot_row, 0));
        }

        // Check for zero pivot
        long double pivot = A(k, k);
        if (std::abs(pivot) < 1e-12)
        {
            throw std::runtime_error("GaussianElimination: zero pivot");
        }

        // Eliminate
        for (size_t i = k + 1; i < n; ++i)
        {
            long double factor = A(i, k) / pivot;
            for (size_t j = k + 1; j < m; ++j)
            {
                A(i, j) -= factor * A(k, j);
            }
            b(i, 0) -= factor * b(k, 0);
        }
    }

    // Backward substitution
    for (size_t i = n - 1; i > 0; --i)
    {
        for (size_t j = i - 1; j < i; --j)
        {
            long double factor = A(j, i) / A(i, i);
            b(j, 0) -= factor * b(i, 0);
        }
    }

    // Scale
    for (size_t i = 0; i < n; ++i)
    {
        long double factor = 1.0 / A(i, i);
        b(i, 0) *= factor;
    }

    x = b;
}
