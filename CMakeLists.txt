cmake_minimum_required(VERSION 3.12)
project(MatrixCurer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -fPIC -Wall -Wextra -pedantic")

# Find pybind11 package
find_package(pybind11 REQUIRED)

# Include directories
include_directories(include)
include_directories(${pybind11_INCLUDE_DIRS})

# Library sources
file(GLOB LIB_SOURCES "src/*.cpp")

# Library target
add_library(MatrixCurer SHARED ${LIB_SOURCES})
set_target_properties(MatrixCurer PROPERTIES PREFIX "")
set_target_properties(MatrixCurer PROPERTIES OUTPUT_NAME "matrix_curer")
target_link_libraries(MatrixCurer PRIVATE pybind11::embed blas)

# Executable target
add_executable(MatrixCurerExe ${LIB_SOURCES})
target_link_libraries(MatrixCurerExe PRIVATE pybind11::embed blas)

# Test target
add_custom_target(test
    COMMAND python3 -m pytest -v -s ${CMAKE_CURRENT_LIST_DIR}/test
    DEPENDS MatrixCurer)

# Set source groups for IDEs
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "Header Files" FILES ${HEADERS})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source Files" FILES ${LIB_SOURCES})
