cmake_minimum_required(VERSION 3.13)
project(mylibrary)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/pybind11/share/cmake/pybind11/")

find_package(pybind11 REQUIRED)

pybind11_add_module(mylibrary MODULE bindings.cpp)