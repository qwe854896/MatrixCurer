#include <cstring>
#include "MatrixCurer/Matrix.h"

// Default constructor
Matrix::Matrix()
    : m_nrow(0), m_ncol(0)
{
}

// Copy constructor
Matrix::Matrix(const Matrix &other)
    : m_nrow(other.m_nrow), m_ncol(other.m_ncol), m_buffer(other.m_buffer)
{
}

// Move constructor
Matrix::Matrix(Matrix &&other) noexcept
    : m_nrow(std::exchange(other.m_nrow, 0)),
      m_ncol(std::exchange(other.m_ncol, 0)),
      m_buffer(std::move(other.m_buffer))
{
}

// Custom constructor
Matrix::Matrix(const size_t &nrow, const size_t &ncol)
    : m_nrow(nrow), m_ncol(ncol), m_buffer(nrow * ncol, 0.0)
{
}

// Copy assignment operator
Matrix &Matrix::operator=(const Matrix &other)
{
    if (this != &other)
    {
        m_nrow = other.m_nrow;
        m_ncol = other.m_ncol;
        m_buffer = other.m_buffer;
    }
    return *this;
}

// Move assignment operator
Matrix &Matrix::operator=(Matrix &&other) noexcept
{
    m_nrow = std::exchange(other.m_nrow, 0);
    m_ncol = std::exchange(other.m_ncol, 0);
    m_buffer = std::move(other.m_buffer);
    return *this;
}

// Destructor
Matrix::~Matrix()
{
    m_buffer.clear();
}

// No bound check.
double Matrix::operator()(const size_t &row, const size_t &col) const
{
    return m_buffer[row * m_ncol + col];
}
double &Matrix::operator()(const size_t &row, const size_t &col)
{
    return m_buffer[row * m_ncol + col];
}

size_t Matrix::nrow() const { return m_nrow; }
size_t Matrix::ncol() const { return m_ncol; }
std::vector<double> &Matrix::buffer() { return m_buffer; }
const std::vector<double> &Matrix::buffer() const { return m_buffer; }

bool Matrix::operator==(const Matrix &other) const
{
    if (nrow() != other.nrow() || ncol() != other.ncol())
        return false;
    for (size_t i = 0; i < nrow(); ++i)
        for (size_t j = 0; j < ncol(); ++j)
            if (operator()(i, j) != other(i, j))
                return false;
    return true;
}
bool Matrix::operator!=(const Matrix &other) const
{
    return !(*this == other);
}