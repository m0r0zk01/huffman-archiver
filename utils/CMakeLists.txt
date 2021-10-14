cmake_minimum_required(VERSION 3.11)
project(Utils)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

add_library(lib_utils command_line_arguments_parser.cpp)