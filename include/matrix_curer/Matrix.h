#pragma once

#include <cstddef>
#include <vector>

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
    virtual ~Matrix();

    // Element access functions
    long double operator()(const size_t &row, const size_t &col) const;
    long double &operator()(const size_t &row, const size_t &col);

    // Size functions
    size_t nrow() const;
    size_t ncol() const;

    // Buffer functions
    std::vector<long double> &buffer();
    const std::vector<long double> &buffer() const;

    // Comparison operators
    bool operator==(const Matrix &other) const;
    bool operator!=(const Matrix &other) const;

    // v1 functions
    // may be move to other place
    Matrix transpose() const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    void svd(Matrix &U, Matrix &S, Matrix &Vt) const;
    void eigen_symmetric(Matrix &eigen_values, Matrix &eigen_vectors) const;
    bool is_symmetric() const;
    void set_identity();
    void resize(const size_t &row, const size_t &col);

private:
    size_t m_nrow;
    size_t m_ncol;
    std::vector<long double> m_buffer;
};
