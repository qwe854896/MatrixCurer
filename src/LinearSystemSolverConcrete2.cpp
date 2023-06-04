#include "matrix_curer/LinearSystemSolverConcrete2.hpp"

#include "matrix_curer/Matrix.hpp"
#include "matrix_curer/MatrixOperation.hpp"
#include "matrix_curer/SVDDecomposer.hpp"
#include "matrix_curer/SVDDecomposerConcrete1.hpp"

#include "matrix_curer/utils.hpp"

void LinearSystemSolverConcrete2::solve(const Matrix &A, const Matrix &b, Matrix &x)
{
    const size_t n = A.nrow();
    const size_t m = A.ncol();

    if (n != b.nrow() || b.ncol() != 1)
    {
        throw std::invalid_argument("solveLinearSystemSVD: b has wrong size");
    }

    // Compute the SVD of A
    SVDDecomposer *decomposer = new SVDDecomposerConcrete1;

    Matrix U, S, Vt;
    decomposer->decompose(A, U, S, Vt);

    // std::cerr << "SVDSolver::solve::A: " << A << std::endl;
    // std::cerr << "SVDSolver::solve::U: " << U << std::endl;
    // std::cerr << "SVDSolver::solve::S: " << S << std::endl;
    // std::cerr << "SVDSolver::solve::Vt: " << Vt << std::endl;
    // std::cerr << "SVDSolver::solve::USVt: " << U * S * Vt << std::endl;

    // Check for singular values close to zero
    const long double threshold = 1e-8 * S(0, 0);
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
        long double val = S(i, i);
        if (val != 0)
        {
            S_inv(i, i) = 1.0 / val;
        }
    }

    // Compute the solution x = V * S_inv * U^T * b
    Matrix U_t = MatrixOperation::transpose(U);
    Matrix V = MatrixOperation::transpose(Vt);

    x = V * S_inv * U_t * b;
}