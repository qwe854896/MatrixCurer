import numpy as np
import pytest

from matrix_curer import Matrix


@pytest.fixture
def numpy_array():
    return np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])


@pytest.fixture
def matrix_curer_matrix():
    return Matrix([[1, 2, 3], [4, 5, 6], [7, 8, 9]])


def test_matrix_creation_from_numpy_array(numpy_array):
    mat = Matrix(numpy_array)
    assert isinstance(mat, Matrix)
    assert np.array_equal(mat.array, numpy_array)


def test_numpy_array_creation_from_matrix(matrix_curer_matrix):
    arr = matrix_curer_matrix.array
    assert isinstance(arr, np.ndarray)
    assert np.array_equal(arr, matrix_curer_matrix.array)
