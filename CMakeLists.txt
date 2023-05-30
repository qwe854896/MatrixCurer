cmake_minimum_required(VERSION 3.12)
project(MatrixCurer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3 -fPIC -Wall -Wextra -pedantic")

find_package(pybind11 REQUIRED)

# Include directories
include_directories(include)

# Link directories
link_directories(lib)

# Library sources
set(LIB_SOURCES
    src/mod.cpp
    src/Matrix.cpp
    src/Multiply.cpp
    src/CustomAllocator.cpp
)

# Library target
add_library(MatrixCurer SHARED ${LIB_SOURCES})
set_target_properties(MatrixCurer PROPERTIES PREFIX "")
set_target_properties(MatrixCurer PROPERTIES OUTPUT_NAME "matrix_curer")
target_link_libraries(MatrixCurer PRIVATE pybind11::embed blas)

add_custom_target(test
    COMMAND python3 -m pytest -v -s ${CMAKE_CURRENT_LIST_DIR}/test
    DEPENDS MatrixCurer)
