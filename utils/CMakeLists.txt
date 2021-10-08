cmake_minimum_required(VERSION 2.8)
project(Utils)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

add_library(lib_utils command_line_arguments_parser.cpp extract_filename.cpp)