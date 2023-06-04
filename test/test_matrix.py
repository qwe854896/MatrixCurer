import random

from matrix_curer import Matrix
from matrix_curer import multiply_naive


MIN_SIZE = 2
MAX_SIZE = 10


def random_matrix(nrow=0, ncol=0, sz_min=MIN_SIZE, sz_max=MAX_SIZE):
    nrow = nrow if nrow != 0 else random.randint(sz_min, sz_max)
    ncol = ncol if ncol != 0 else random.randint(sz_min, sz_max)
    return Matrix(nrow, ncol), nrow, ncol


def test_matrix_creation():
    try:
        _ = Matrix(3, 4)
        assert True
    except:
        assert False


def test_empty_matrix():
    try:
        _ = Matrix(0, 0)
        assert False
    except:
        assert True


def test_empty_row_matrix():
    try:
        _ = Matrix(0, 5)
        assert False
    except:
        assert True


def test_empty_col_matrix():
    try:
        _ = Matrix(5, 0)
        assert False
    except:
        assert True


def test_scalar_matrix():
    try:
        _ = Matrix(1, 1)
        assert True
    except:
        assert False


def test_getitem():
    mat, nrow, ncol = random_matrix()
    for i in range(nrow):
        for j in range(ncol):
            _ = mat[i, j]
            assert _ == 0.0


def test_setitem():
    mat, nrow, ncol = random_matrix()
    for i in range(nrow):
        for j in range(ncol):
            mat[i, j] = (i + 1) * (j + 1)
            assert mat[i, j] == (i + 1) * (j + 1)


def test_getter():
    mat, nrow, ncol = random_matrix()
    assert nrow == mat.nrow
    assert ncol == mat.ncol


def test_equal_comparator():
    mat1, nrow, ncol = random_matrix()
    mat2, nrow, ncol = random_matrix(nrow=nrow, ncol=ncol)

    for i in range(nrow):
        for j in range(ncol):
            mat1[i, j] = i * j
            mat2[i, j] = i * j

    assert mat1 == mat2


def test_inequal_comparator():
    mat1, nrow, ncol = random_matrix(sz_min=2)
    mat2, nrow, ncol = random_matrix(nrow=nrow, ncol=ncol)

    for i in range(nrow):
        for j in range(ncol):
            mat1[i, j] = i + j
            mat2[i, j] = i - j

    assert mat1 != mat2


def test_addition():
    mat1, nrow, ncol = random_matrix(sz_min=2)
    mat2, nrow, ncol = random_matrix(nrow=nrow, ncol=ncol)

    for i in range(nrow):
        for j in range(ncol):
            mat1[i, j] = random.randint(-100, 100)
            mat2[i, j] = random.randint(-100, 100)

    mat = mat1 + mat2
    for i in range(nrow):
        for j in range(ncol):
            assert mat[i, j] == mat1[i, j] + mat2[i, j]


def test_substraction():
    mat1, nrow, ncol = random_matrix(sz_min=2)
    mat2, nrow, ncol = random_matrix(nrow=nrow, ncol=ncol)

    for i in range(nrow):
        for j in range(ncol):
            mat1[i, j] = random.randint(-100, 100)
            mat2[i, j] = random.randint(-100, 100)

    mat = mat1 - mat2
    for i in range(nrow):
        for j in range(ncol):
            assert mat[i, j] == mat1[i, j] - mat2[i, j]


def test_multiplication():
    size = 100
    mat1 = Matrix(size, size)
    mat2 = Matrix(size, size)

    for i in range(size):
        for j in range(size):
            mat1[i, j] = i * size + j + 1
            mat2[i, j] = i * size + j + 1

    mat = mat1 * mat2
    mat_naive = multiply_naive(mat1, mat2)

    assert mat == mat_naive


def test_unary_negation():
    mat1, nrow, ncol = random_matrix(sz_min=2)

    for i in range(nrow):
        for j in range(ncol):
            mat1[i, j] = random.randint(-100, 100)

    mat = -mat1
    for i in range(nrow):
        for j in range(ncol):
            assert mat[i, j] == -mat1[i, j]


def test_copy_constructor():
    mat1, _, _ = random_matrix()
    mat2 = Matrix(mat1)
    assert mat1 == mat2


def test_copy_constructor_deep_copy():
    mat1, _, _ = random_matrix(sz_min=3)
    mat2 = Matrix(mat1)
    
    mat1[1, 1] = 2
    mat2[1, 1] = 3
    
    assert mat1 != mat2
