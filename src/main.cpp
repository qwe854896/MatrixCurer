#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>

#include "matrix_curer/Matrix.hpp"
#include "matrix_curer/LinearSystemSolver.hpp"
#include "matrix_curer/LinearSystemSolverConcrete1.hpp"
#include "matrix_curer/LinearSystemSolverConcrete2.hpp"

Matrix hilbertMatrix(int n)
{
    Matrix A(n, n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            A(i, j) = 1.0 / (i + j + 1);
        }
    }
    return A;
}

void printResults(int n, long double error)
{
    std::cout << std::setw(2) << n << " ";
    std::cout << std::scientific << std::setprecision(6);
    std::cout << std::setw(20) << error << std::endl;
}

void printResultsForSolver(int i, const Matrix &H, const Matrix &b, const Matrix &x, Matrix &xx, LinearSystemSolver *solver)
{
    solver->solve(H, b, xx);
    // long double conditionNumber = H.norm() * H.inverse().norm();

    Matrix residual = x - xx;
    double error = 0;
    for (int j = 0; j < i; ++j)
        error = std::max(error, std::abs(residual(j, 0)));

    printResults(i, error);
}

int main()
{
    LinearSystemSolver *gaussian_elimination_solver = new LinearSystemSolverConcrete1;
    LinearSystemSolver *svd_solver = new LinearSystemSolverConcrete2;

    std::cout << std::setw(10) << "n";
    std::cout << std::setw(20) << "cond";
    std::cout << std::setw(30) << "error" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    for (int i = 4; i <= 16; ++i)
    {
        Matrix x = Matrix(i, 1);
        for (int j = 0; j < i; ++j)
            x(j, 0) = 1.0;

        Matrix H = hilbertMatrix(i);
        Matrix b = H * x;
        Matrix xx(i, 1);

        printResultsForSolver(i, H, b, x, xx, svd_solver);
    }

    std::cout << std::setw(10) << "n";
    std::cout << std::setw(20) << "cond";
    std::cout << std::setw(30) << "error" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    for (int i = 4; i <= 16; ++i)
    {
        Matrix x = Matrix(i, 1);
        for (int j = 0; j < i; ++j)
            x(j, 0) = 1.0;

        Matrix H = hilbertMatrix(i);
        Matrix b = H * x;
        Matrix xx(i, 1);

        printResultsForSolver(i, H, b, x, xx, gaussian_elimination_solver);
    }

    return 0;
}
