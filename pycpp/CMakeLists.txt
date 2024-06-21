cmake_minimum_required(VERSION 3.13)
project(mylibrary)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/pybind11/share/cmake/pybind11/")

# Find pybind11 package
find_package(pybind11 REQUIRED)

# Include pybind11 headers
include_directories(${pybind11_INCLUDE_DIRS})

# Define the library
pybind11_add_module(mylibrary bindings.cpp Box.cpp)

# Link libraries
target_link_libraries(mylibrary PRIVATE pybind11::module)
