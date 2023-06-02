#pragma once

#include "LinearSystemSolver.hpp"

class LinearSystemSolverConcrete2 : public LinearSystemSolver
{
public:
    virtual void solve(const Matrix &A, const Matrix &b, Matrix &x) override;
};