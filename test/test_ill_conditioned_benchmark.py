# import numpy as np
# from numpy.linalg import norm, cond, solve
# import pytest

# from matrix_curer import solve as matrix_curer_solve


# def hilbert_matrix(n):
#     A = np.zeros((n, n))
#     for i in range(n):
#         for j in range(n):
#             A[i, j] = 1 / (i + j + 1)
#     return A


# def main(benchmark):
#     print("{:10s} {:20s} {:30s}".format("n", "cond", "error"))
#     print("-" * 50)

#     solutions = []

#     for i in range(4, 17):
#         x = np.ones(i)
#         H = hilbert_matrix(i)
#         b = H.dot(x)

#         c = cond(H)

#         # benchmark measurements
#         xx = benchmark(solve, H, b)
#         err = norm(x - xx, np.inf) / norm(x, np.inf)
#         solutions.append(xx)

#         print("{:2d} {:20e} {:20e}".format(i, c, err))


# @pytest.mark.benchmark(group="matrix_curer")
# def test_matrix_curer_solve(benchmark):
#     def solve_wrapper(A, b):
#         return matrix_curer_solve(A, b)

#     main(benchmark.pedantic(solve_wrapper, args=(
#         np.array([]), np.array([])), iterations=1, rounds=10))


# @pytest.mark.benchmark(group="numpy")
# def test_numpy_solve(benchmark):
#     main(benchmark.pedantic(solve, args=(
#         np.array([]), np.array([])), iterations=1, rounds=10))


# if __name__ == '__main__':
#     pytest.main(["-v"])
