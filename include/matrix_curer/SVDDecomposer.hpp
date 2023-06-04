#pragma once

#include <tuple>

#include "Matrix.hpp"

class SVDDecomposer
{
public:
    virtual ~SVDDecomposer() {}
    virtual void decompose(const Matrix &A, Matrix &U, Matrix &S, Matrix &Vt) = 0;
};