#pragma once

#include "SVDDecomposer.hpp"

class SVDDecomposerConcrete1 : public SVDDecomposer
{
public:
    virtual std::tuple<Matrix, Matrix, Matrix> decompose(const Matrix &A) override;
};