#pragma once

#include "Matrix.hpp"

class MatrixMultiplication
{
public:
    static Matrix &multiply_naive(const Matrix &mat1, const Matrix &mat2);
    static Matrix &multiply_tile(const Matrix &mat1, const Matrix &mat2, size_t tsize);
    static Matrix &multiply_mkl(const Matrix &mat1, const Matrix &mat2);
};
