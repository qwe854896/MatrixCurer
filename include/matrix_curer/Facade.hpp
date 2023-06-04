#pragma once

#include <tuple>
#include <string>

#include "Matrix.hpp"

class MatrixCurer
{
public:
    static Matrix &solveLinearSystem(const Matrix &A, const Matrix &b, const std::string &strategy = "");
    static std::tuple<Matrix, Matrix, Matrix> decomposeSVD(const Matrix &A, const std::string &strategy = "");
};
