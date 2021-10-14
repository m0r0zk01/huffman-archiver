cmake_minimum_required(VERSION 3.11)
project(Reader)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

add_library(lib_reader file_reader.cpp)
