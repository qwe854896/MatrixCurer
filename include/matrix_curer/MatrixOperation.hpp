#pragma once

#include "Matrix.hpp"

class MatrixOperation
{
public:
    static Matrix transpose(const Matrix &matrix);
    static Matrix inverse(const Matrix &matrix);
    static bool is_symmetric(const Matrix &matrix);

    static Matrix Identity(const size_t &size);
    static void set_identity(Matrix &A);
    static void resize(Matrix &A, const size_t &row, const size_t &col);
};
