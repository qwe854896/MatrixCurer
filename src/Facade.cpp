#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "matrix_curer/Facade.hpp"
#include "matrix_curer/LinearSystemSolverConcrete1.hpp"
#include "matrix_curer/LinearSystemSolverConcrete2.hpp"
#include "matrix_curer/SVDDecomposerConcrete1.hpp"
#include "matrix_curer/SVDDecomposerConcrete2.hpp"

namespace py = pybind11;

Matrix &MatrixCurer::solveLinearSystem(const Matrix &A, const Matrix &b, const std::string &strategy)
{
    std::size_t n = A.ncol();

    Matrix *x_mat = new Matrix(n, 1);

    // Create the linear system solver based on the strategy
    std::unique_ptr<LinearSystemSolver> solver;

    if (strategy == "" || strategy == "concrete1")
    {
        solver = std::make_unique<LinearSystemSolverConcrete1>();
    }
    else if (strategy == "concrete2")
    {
        solver = std::make_unique<LinearSystemSolverConcrete2>();
    }
    else
    {
        throw std::runtime_error("Invalid strategy");
    }

    // Solve the linear system
    solver->solve(A, b, *x_mat);

    return *x_mat;
}

std::tuple<Matrix, Matrix, Matrix> MatrixCurer::decomposeSVD(const Matrix &A, const std::string &strategy)
{
    // Create the SVD decomposer based on the strategy
    std::unique_ptr<SVDDecomposer> decomposer;

    if (strategy == "" || strategy == "concrete1")
    {
        decomposer = std::make_unique<SVDDecomposerConcrete1>();
    }
    else if (strategy == "concrete2")
    {
        decomposer = std::make_unique<SVDDecomposerConcrete2>();
    }
    else
    {
        throw std::runtime_error("Invalid strategy");
    }

    // Perform the SVD decomposition
    Matrix U, S, Vt;
    decomposer->decompose(A, U, S, Vt);

    // Matrix *U = new Matrix(std::get<0>(decomposition));
    // Matrix *S = new Matrix(std::get<1>(decomposition));
    // Matrix *Vt = new Matrix(std::get<2>(decomposition));

    // std::tuple<Matrix, Matrix, Matrix> *ret = new std::tuple<Matrix, Matrix, Matrix>(decomposition);

    return std::make_tuple(U, S, Vt);
}