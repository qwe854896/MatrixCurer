#pragma once

#include <cstddef>
#include <vector>

#include "CustomAllocator.hpp"

class Matrix
{
public:
    // Default constructor
    Matrix();

    // Copy constructor
    Matrix(const Matrix &other);

    // Move constructor
    Matrix(Matrix &&other) noexcept;

    // Custom constructor
    Matrix(const size_t &row, const size_t &col);

    // Copy assignment operator
    Matrix &operator=(const Matrix &other);

    // Move assignment operator
    Matrix &operator=(Matrix &&other) noexcept;

    // Destructor
    ~Matrix();

    // Friend class
    friend class MatrixOperation;

    // Element access functions
    double operator()(const size_t &row, const size_t &col) const;
    double &operator()(const size_t &row, const size_t &col);

    // Size functions
    size_t nrow() const;
    size_t ncol() const;

    // Buffer functions
    std::vector<double, CustomAllocator<double>> &buffer();
    const std::vector<double, CustomAllocator<double>> &buffer() const;

    // Comparison operators
    bool operator==(const Matrix &other) const;
    bool operator!=(const Matrix &other) const;

    // Arithmetic operators
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Matrix operator-() const;

private:
    size_t m_nrow;
    size_t m_ncol;
    std::vector<double, CustomAllocator<double>> m_buffer;
};
