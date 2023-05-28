#include "MatrixCurer/utils.h"

std::ostream &operator<<(std::ostream &os, const Matrix &A)
{
    const size_t nrow = A.nrow();
    const size_t ncol = A.ncol();

    os << std::endl;
    for (size_t i = 0; i < nrow; ++i)
    {
        for (size_t j = 0; j < ncol; ++j)
        {
            os << A(i, j) << " ";
        }
        os << std::endl;
    }

    return os;
}