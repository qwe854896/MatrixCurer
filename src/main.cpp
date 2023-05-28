#include <iomanip>

#include "MatrixCurer/utils.h"
#include "MatrixCurer/Matrix.h"
#include "MatrixCurer/LinearSystemSolver.h"

int main()
{
    LinearSystemSolver *solver = new GaussianEliminationSolver;

    std::cout << std::fixed << std::setprecision(11);

    // Define the matrix A and the vector b for an ill-conditioned system
    Matrix A(2, 2);
    A(0, 0) = 0.540;
    A(0, 1) = 0.323;
    A(1, 0) = 0.647;
    A(1, 1) = 0.387;

    Matrix b(2, 1);
    b(0, 0) = 0.864;
    b(1, 0) = 1.034;

    // Solve the linear system using Gaussian elimination
    Matrix x_gauss(2, 1);

    solver = new SVDSolver;
    solver->solve(A, b, x_gauss);
    delete solver;

    // Solve the linear system using SVD
    Matrix x_svd(2, 1);

    solver = new GaussianEliminationSolver;
    solver->solve(A, b, x_svd);
    delete solver;

    // Print the solutions
    std::cout << "Solution using Gaussian elimination: " << x_gauss << std::endl;
    std::cout << "Ax = " << A * x_gauss << std::endl;

    std::cout << "Solution using SVD: " << x_svd << std::endl;
    std::cout << "Ax = " << A * x_svd << std::endl;

    return 0;
}
