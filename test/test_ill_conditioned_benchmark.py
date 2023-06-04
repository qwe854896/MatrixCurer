import numpy as np
from numpy.linalg import norm, cond, solve

from matrix_curer import Matrix
from matrix_curer import solve as matrix_curer_solve


def hilbert_matrix(n):
    A = np.zeros((n, n))
    for i in range(n):
        for j in range(n):
            A[i, j] = 1 / (i + j + 1)
    return A


def test_numpy_solve():
    print("{:10s} {:20s} {:30s}".format("n", "cond", "error"))
    print("-" * 50)

    for i in range(4, 17):
        x = np.ones(i)
        H = hilbert_matrix(i)
        b = H.dot(x)

        c = cond(H)

        xx = solve(H, b)
        err = norm(x - xx, np.inf) / norm(x, np.inf)

        print("{:2d} {:20e} {:20e}".format(i, c, err))


def test_matrix_curer_solve():
    print("{:10s} {:20s} {:30s}".format("n", "cond", "error"))
    print("-" * 50)

    for i in range(4, 17):
        x = np.ones(i)
        H = hilbert_matrix(i)
        b = H.dot(x)
        c = cond(H)

        b = np.reshape(b, (-1, 1))
        H, b = Matrix(H), Matrix(b)
        xx = matrix_curer_solve(H, b, "concrete1")
        xx = xx.array

        err = norm(x - xx, np.inf) / norm(x, np.inf)

        print("{:2d} {:20e} {:20e}".format(i, c, err))
