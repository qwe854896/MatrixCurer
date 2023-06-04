#pragma once

#include "SVDDecomposer.hpp"

class SVDDecomposerConcrete1 : public SVDDecomposer
{
public:
    virtual void decompose(const Matrix &A, Matrix &U, Matrix &S, Matrix &Vt) override;
};