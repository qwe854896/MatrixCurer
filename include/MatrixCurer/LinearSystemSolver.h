#pragma once

class Matrix;

class LinearSystemSolver
{
public:
    virtual ~LinearSystemSolver() {}

    virtual void solve(Matrix A, Matrix b, Matrix &x) = 0;
};

class GaussianEliminationSolver : public LinearSystemSolver
{
public:
    virtual void solve(Matrix A, Matrix b, Matrix &x) override;

private:
    const double kEpsilon = 1e-8;
};

class SVDSolver : public LinearSystemSolver
{
public:
    virtual void solve(Matrix A, Matrix b, Matrix &x) override;

private:
    const double kEpsilon = 1e-8;
};