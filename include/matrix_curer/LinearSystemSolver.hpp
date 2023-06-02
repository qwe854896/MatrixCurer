#pragma once

#include "Matrix.hpp"

class LinearSystemSolver
{
public:
    virtual ~LinearSystemSolver() {}
    virtual void solve(const Matrix &A, const Matrix &b, Matrix &x) = 0;
};