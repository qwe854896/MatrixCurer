# import numpy as np
# from numpy.linalg import norm, cond, solve


# def hilbert_matrix(n):
#     A = np.zeros((n, n))
#     for i in range(n):
#         for j in range(n):
#             A[i, j] = 1 / (i + j + 1)
#     return A


# def main():
#     print("{:10s} {:20s} {:30s}".format("n", "cond", "error"))
#     print("-" * 50)

#     solutions = []

#     for i in range(4, 17):
#         x = np.ones(i)
#         H = hilbert_matrix(i)
#         b = H.dot(x)

#         c = cond(H)
#         xx = solve(H, b)
#         err = norm(x - xx, np.inf) / norm(x, np.inf)
#         solutions.append(xx)

#         print("{:2d} {:20e} {:20e}".format(i, c, err))


# if __name__ == '__main__':
#     main()
