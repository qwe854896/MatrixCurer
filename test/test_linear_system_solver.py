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


@pytest.mark.parametrize("tolerance", [1e-6])  # Adjust tolerance as needed
@pytest.mark.parametrize("strategy", ["", "concrete1", "concrete2"])
@pytest.mark.parametrize("shape", [(2, 2), (4, 2), (2, 4)])
def test_linear_system_solver(tolerance, strategy, shape):
    A = Matrix(shape[0], shape[1])

    for i in range(shape[0]):
        for j in range(shape[1]):
            A[i, j] = i * shape[1] + j + 1

    x = Matrix(shape[1], 1)

    for j in range(shape[1]):
        x[j, 0] = j * (-1 + 2 * (j & 1))

    b = A * x
    x_ = solve(A, b, strategy)
    b_ = A * x_

    assert np.allclose(b.array, b_.array, atol=tolerance)
