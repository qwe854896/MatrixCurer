#pragma once

#include "Matrix.h"

Matrix &multiply_naive(const Matrix &mat1, const Matrix &mat2);
Matrix &multiply_tile(const Matrix &mat1, const Matrix &mat2, size_t tsize);
Matrix &multiply_mkl(const Matrix &mat1, const Matrix &mat2);