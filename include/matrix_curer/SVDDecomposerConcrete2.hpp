#pragma once

#include "SVDDecomposer.hpp"

class SVDDecomposerConcrete2 : public SVDDecomposer
{
public:
    virtual void decompose(const Matrix &A, Matrix &U, Matrix &S, Matrix &Vt) override;
};