import random
import numpy as np
import pytest

from matrix_curer import Matrix

MIN_SIZE = 1
MAX_SIZE = 10


def random_matrix(nrow=0, ncol=0, sz_min=MIN_SIZE, sz_max=MAX_SIZE):
    nrow = nrow if nrow != 0 else random.randint(sz_min, sz_max)
    ncol = ncol if ncol != 0 else random.randint(sz_min, sz_max)
    return Matrix(nrow, ncol), nrow, ncol


@pytest.mark.parametrize("tolerance", [1e-6])  # Adjust tolerance as needed
@pytest.mark.parametrize("strategy", ["", "concrete1", "concrete2"])
# @pytest.mark.parametrize("shape", [(5, 5), (5, 10), (10, 5)])
@pytest.mark.parametrize("shape", [(5, 5)])
def test_svd(tolerance, strategy, shape):
    mat, nrow, ncol = random_matrix(nrow=shape[0], ncol=shape[1], sz_min=5)

    for i in range(nrow):
        for j in range(ncol):
            mat[i, j] = i * ncol + j

    U, S, Vt = mat.svd(strategy)
    reconstructed_matrix = U * S * Vt

    assert np.allclose(mat.array, reconstructed_matrix.array, atol=tolerance)
