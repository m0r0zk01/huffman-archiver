cmake_minimum_required(VERSION 2.8)
project(archiver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

add_executable(archiver.sh main.cpp)

add_subdirectory(./archiver)
add_subdirectory(./reader)
add_subdirectory(./writer)
add_subdirectory(./trie)
add_subdirectory(./utils)

target_link_libraries(archiver.sh ARCHIVER READER WRITER TRIE UTILS)
