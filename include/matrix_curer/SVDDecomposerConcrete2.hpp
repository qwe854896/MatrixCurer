#pragma once

#include "SVDDecomposer.hpp"

class SVDDecomposerConcrete2 : public SVDDecomposer
{
public:
    virtual std::tuple<Matrix, Matrix, Matrix> decompose(const Matrix &A) override;
};