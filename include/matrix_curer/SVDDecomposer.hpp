#pragma once

#include <tuple>

#include "Matrix.hpp"

class SVDDecomposer
{
public:
    virtual ~SVDDecomposer() {}
    virtual std::tuple<Matrix, Matrix, Matrix> decompose(const Matrix &A) = 0;
};