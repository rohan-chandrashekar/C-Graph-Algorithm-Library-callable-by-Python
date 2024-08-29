cmake_minimum_required(VERSION 3.0)
project(graphlib)

set(CMAKE_CXX_STANDARD 14)

find_package(pybind11 REQUIRED)

pybind11_add_module(graphlib graph_bindings.cpp graph.h)