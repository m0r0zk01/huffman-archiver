cmake_minimum_required(VERSION 2.8)
project(Archiver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

add_library(ARCHIVER archiver.cpp compressor.cpp decompressor.cpp)

# Setup testing
#file(COPY ../tests/mock DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
#
#link_directories(/usr/local/lib)
#
#enable_testing()
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIR})
#
#file(GLOB TEST_FILES "tests/*.cpp")
#add_executable("test_archiver" EXCLUDE_FROM_ALL ${TEST_FILES})
#target_link_libraries("test_archiver" gtest pthread ARCHIVER READER WRITER TRIE)
#add_dependencies(test_archiver "test_archiver")
#add_test("test_archiver" "./test_archiver")