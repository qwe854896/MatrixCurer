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
    assert np.array_equal(mat.data, numpy_array)


def test_numpy_array_creation_from_matrix(matrix_curer_matrix):
    arr = np.array(matrix_curer_matrix)
    assert isinstance(arr, np.ndarray)
    assert np.array_equal(arr, matrix_curer_matrix.data)


def test_addition(numpy_array, matrix_curer_matrix):
    result = matrix_curer_matrix + numpy_array
    expected = matrix_curer_matrix.data + numpy_array
    assert isinstance(result, Matrix)
    assert np.array_equal(result.data, expected)


def test_subtraction(numpy_array, matrix_curer_matrix):
    result = matrix_curer_matrix - numpy_array
    expected = matrix_curer_matrix.data - numpy_array
    assert isinstance(result, Matrix)
    assert np.array_equal(result.data, expected)


def test_multiplication(numpy_array, matrix_curer_matrix):
    result = matrix_curer_matrix * numpy_array
    expected = matrix_curer_matrix.data * numpy_array
    assert isinstance(result, Matrix)
    assert np.array_equal(result.data, expected)


def test_transpose(matrix_curer_matrix):
    result = matrix_curer_matrix.transpose()
    expected = matrix_curer_matrix.data.T
    assert isinstance(result, Matrix)
    assert np.array_equal(result.data, expected)


def test_dot_product(numpy_array, matrix_curer_matrix):
    result = matrix_curer_matrix.dot(numpy_array)
    expected = matrix_curer_matrix.data.dot(numpy_array)
    assert isinstance(result, Matrix)
    assert np.array_equal(result.data, expected)


def test_elementwise_multiplication(numpy_array, matrix_curer_matrix):
    result = matrix_curer_matrix.elementwise_multiply(numpy_array)
    expected = matrix_curer_matrix.data * numpy_array
    assert isinstance(result, Matrix)
    assert np.array_equal(result.data, expected)
