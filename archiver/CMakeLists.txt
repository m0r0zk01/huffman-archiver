cmake_minimum_required(VERSION 2.8)
project(Archiver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

add_library(lib_archiver archiver.cpp compressor.cpp decompressor.cpp)
