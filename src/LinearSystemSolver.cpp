#include "MatrixCurer/LinearSystemSolver.h"
#include "MatrixCurer/Matrix.h"
#include "MatrixCurer/utils.h"

void GaussianEliminationSolver::solve(Matrix A, Matrix b, Matrix &x)
{
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
        double pivot_value = std::abs(A(k, k));
        for (size_t i = k + 1; i < n; ++i)
        {
            double abs_value = std::abs(A(i, k));
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
        double pivot = A(k, k);
        if (std::abs(pivot) < kEpsilon)
        {
            throw std::runtime_error("GaussianElimination: zero pivot");
        }

        // Eliminate
        for (size_t i = k + 1; i < n; ++i)
        {
            double factor = A(i, k) / pivot;
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
            double factor = A(j, i) / A(i, i);
            b(j, 0) -= factor * b(i, 0);
        }
    }

    // Scale
    for (size_t i = 0; i < n; ++i)
    {
        double factor = 1.0 / A(i, i);
        b(i, 0) *= factor;
    }

    x = b;
}

void SVDSolver::solve(Matrix A, Matrix b, Matrix &x)
{
    const size_t n = A.nrow();
    const size_t m = A.ncol();

    if (n != b.nrow() || b.ncol() != 1)
    {
        throw std::invalid_argument("solveLinearSystemSVD: b has wrong size");
    }

    // Compute the SVD of A
    Matrix U, S, Vt;
    A.svd(U, S, Vt);

    std::cerr << "SVDSolver::solve::A: " << A << std::endl;
    std::cerr << "SVDSolver::solve::U: " << U << std::endl;
    std::cerr << "SVDSolver::solve::S: " << S << std::endl;
    std::cerr << "SVDSolver::solve::Vt: " << Vt << std::endl;
    std::cerr << "SVDSolver::solve::USVt: " << U * S * Vt << std::endl;

    // Check for singular values close to zero
    const double threshold = kEpsilon * S(0, 0);
    for (size_t i = 0; i < m; ++i)
    {
        if (std::abs(S(i, i)) < threshold)
        {
            throw std::runtime_error("solveLinearSystemSVD: singular matrix");
        }
    }

    // Compute the pseudo-inverse of S
    Matrix S_inv(m, n);
    for (size_t i = 0; i < m; ++i)
    {
        double val = S(i, i);
        if (val != 0)
        {
            S_inv(i, i) = 1.0 / val;
        }
    }

    // Compute the solution x = V * S_inv * U^T * b
    Matrix U_t = U.transpose();
    Matrix V = Vt.transpose();

    x = V * S_inv * U_t * b;
}