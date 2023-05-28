cmake_minimum_required(VERSION 3.0)

project(MatrixCurer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Library sources
set(LIB_SOURCES
    src/utils.cpp
    src/Matrix.cpp
    src/LinearSystemSolver.cpp
)

# Library target
add_library(MatrixCurerLib ${LIB_SOURCES})

# Executable sources
set(EXE_SOURCES
    src/main.cpp
)

# Executable target
add_executable(MatrixCurer ${EXE_SOURCES})

# Link executable with library
target_link_libraries(MatrixCurer MatrixCurerLib)

# Tests
# add_subdirectory(test)
