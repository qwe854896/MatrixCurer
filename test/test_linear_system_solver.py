import random
import numpy as np
import pytest

from matrix_curer import Matrix
from matrix_curer import solve

MIN_SIZE = 1
MAX_SIZE = 10


def random_matrix(nrow=0, ncol=0, sz_min=MIN_SIZE, sz_max=MAX_SIZE):
    nrow = nrow if nrow != 0 else random.randint(sz_min, sz_max)
    ncol = ncol if ncol != 0 else random.randint(sz_min, sz_max)
    return Matrix(nrow, ncol), nrow, ncol


def test_linear_system_solver():
    A = Matrix(2, 2)
    A[0, 0] = 1
    A[0, 1] = 2
    A[1, 0] = 3
    A[1, 1] = 4

    x = Matrix(2, 1)
    x[0, 0] = 2
    x[1, 0] = 3

    b = A * x
    x_ = solve(A, b)
    assert np.allclose(x.array, x.array_)
