import random

from matrix_curer import Matrix
from matrix_curer import Identity

MIN_SIZE = 1
MAX_SIZE = 10


def random_matrix(nrow=0, ncol=0, sz_min=MIN_SIZE, sz_max=MAX_SIZE):
    nrow = nrow if nrow != 0 else random.randint(sz_min, sz_max)
    ncol = ncol if ncol != 0 else random.randint(sz_min, sz_max)
    return Matrix(nrow, ncol), nrow, ncol


def test_matrix_transpose():
    mat, nrow, ncol = random_matrix(sz_min=2)

    for i in range(nrow):
        for j in range(ncol):
            mat[i, j] = i * ncol + j + 1

    mat_t = mat.T

    assert mat.nrow == mat_t.ncol
    assert mat.ncol == mat_t.nrow

    for i in range(nrow):
        for j in range(ncol):
            assert mat_t[i, j] == mat[j, i]


def test_matrix_set_identity():
    size = random.randint(10, 30)
    mat = Matrix(size, size)

    mat.set_identity()

    for i in range(size):
        for j in range(size):
            assert (i == j and mat[i, j] == 1) or (i != j and mat[i, j] == 0)


def test_matrix_identity():
    size = random.randint(10, 30)
    mat = Identity(size)

    for i in range(size):
        for j in range(size):
            assert (i == j and mat[i, j] == 1) or (i != j and mat[i, j] == 0)


def test_matrix_inverse():
    size = 30
    mat = Matrix(size, size)

    for i in range(size):
        for j in range(size):
            mat[i, j] = i * size + j + 1

    mat_i = mat.inv()

    I = Identity(size)

    assert I == mat * mat_i
    assert I == mat_i * mat
