===========================================================
MatrixCurer  for  Solving  Ill-Conditioned  Linear  Systems
===========================================================

MatrixCurer: a C++ library for solving ill-conditioned linear systems that
provide seamless interface with numpy ndarray.

Basic Information
=================

There are many libraries which can solve linear systems. But they may suffer
from approximation error when solving ill-conditioned linear systems.

MatrixCurer is a C++ library that provides an efficient and scalable
solution for solving ill-conditioned linear systems.

There are many existing techniques related to solving ill-conditioned
linear systems:

1. Tikhonov regularization
2. Truncated SVD

Problem to Solve
================

Ill-conditioned linear systems often arise in a variety of scientific
and engineering applications, and solving them can be challenging due
to numerical instability.

Existing methods can be computationally
expensive or require significant manual intervention, making them
impractical for many real-world problems.

MatrixCurer aims to provide
an efficient and easy-to-use solution for solving ill-conditioned linear
systems, enabling researchers and practitioners to focus on their
domain-specific tasks without worrying about numerical issues.

Prospective Users
=================

MatrixCurer is intended for researchers and practitioners in a wide range
of fields, including physics, engineering, computer science, and applied
mathematics. It is designed to be easy to use and integrate with existing
codebases, making it accessible to both novice and experienced users.

System Architecture
===================

MatrixCurer is developed in C++ and does not depend on Python. The library
utilizes a template class in C++ that can convert Python built-in lists or
numpy ndarrays for further computation. It leverages state-of-the-art numerical
algorithms to provide an efficient and scalable solution for solving ill-conditioned
linear systems.

The workflow of the system involves pre-processing the input matrix,
followed by iterative refinement of the solution vector until a convergence
criterion is met.

C++ Components:

* MatrixCurer's C++ components handle the core functionality of solving ill-conditioned linear systems using a template class.
* The components are designed to be versatile, supporting different data types and seamless integration with existing codebases.

Control Flow:

1. User initiates the linear system solving process by calling MatrixCurer functions in C++ or Python.
2. It then enters the MatrixCurer library and performs pre-processing on the input matrix.
3. Numerical algorithms are applied to solve the ill-conditioned linear system iteratively.
4. Once the solution vector is obtained, the result is returned to the user's code or script.

Data Flow:

1. User provides the input matrix as a numpy ndarray in Python or a C++ data structure.
2. pybind11 binds the C++ components to Python, enabling interoperability.
3. The input matrix is passed from Python to C++ using the numpy ndarray interface.
4. C++ components compute the solution vector and return it to Python using the numpy ndarray interface.

Unit Tests:

* MatrixCurer's unit tests ensure the correctness of the library's functionality using the Pytest framework.
* Test cases cover input validation, computation correctness, and performance.

Pybind11 Binding:

* pybind11 is used to bind MatrixCurer's C++ components to Python.
* C++ classes, functions, and data structures are exposed using pybind11 macros and functions.
* The binding code is compiled into a shared library or module that can be imported in Python.
* Users can access and use the C++ components from Python.


API Description
===============

MatrixCurer can be programmed in both C++ and Python. In C++, users can call
the library functions by including the header files and linking with the library.
In Python, users can use the numpy ndarray interface to pass the input matrix to
the C++ library and retrieve the output solution vector.

The library provides a range of configuration options, including tolerance levels
and convergence criteria, to enable users to fine-tune the solution process.

Class `Matrix`:

* `__init__(*args)`: Constructor method for the Matrix class.
* `__getitem__(indices)`: Getitem method to access elements of the matrix using indices.
* `__setitem__(indices, value)`: Setitem method to set the value of an element in the matrix.
* `__eq__(other)`: Equality comparator method for Matrix objects.
* `__ne__(other)`: Inequality comparator method for Matrix objects.
* `__neg__()`: Unary negation method for Matrix objects.
* `__add__(other)`: Addition method for Matrix objects.
* `__sub__(other)`: Subtraction method for Matrix objects.
* `__mul__(other)`: Multiplication method for Matrix objects.
* `T()`: Transpose method to get the transpose of the matrix.
* `set_identity()`: Method to set the matrix as an identity matrix.
* `inv()`: Method to compute the inverse of the matrix.

Function `solve(matrix, vector, strategy="")`:
- Solve a linear system of equations using a specified strategy.

Engineering Infrastructure
==========================

MatrixCurer uses CMake as an automatic build system, allowing users to easily build
the library on their respective platforms. The library is hosted on GitHub and
utilizes Git for version control, enabling easy collaboration on the codebase.

Pytest is used for unit testing, ensuring the correctness of the library's
functionality. The library also adopts reStructuredText for documentation.

All new features developed will have corresponding unit tests, and the correctness
of the library is verified by comparing the results obtained from computations
carried out in C++ with those in numpy, ensuring identical results.

Schedule
========

Week 1 (4/10):
  Research and implement state-of-the-art numerical algorithms for solving
  ill-conditioned linear systems.

Week 2 (4/17):
  Develop test cases and follow test-driven development.

Week 3 (4/24):
  Implement the C++ library functions and develop the numpy ndarray interface.

Week 4 (5/1):
  Refactoring week (and accommmodation of overflown work).

Week 5 (5/8):
  Add parallelization by introducing third-party thread manging library.

Week 6 (5/15):
  Optimize the library performance and finalize the API documentation.

Week 7 (5/22):
  Refactoring week (and accommmodation of overflown work).

Week 8 (5/29):
  Refine the library based on issues and develop a roadmap for future
  development.

References
==========

* Trefethen, L. N. (1997). Numerical linear algebra. SIAM.
* Demmel, J. (1997). Applied numerical linear algebra. SI
