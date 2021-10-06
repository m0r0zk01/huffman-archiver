cmake_minimum_required(VERSION 2.8)
project(Reader)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

add_library(READER reader.cpp)

# Setup testing
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/mock DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

link_directories(/usr/local/lib)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_custom_target(test_reader COMMAND GTEST_COLOR=yes ${CMAKE_CTEST_COMMAND} --verbose)

file(GLOB TEST_FILES "tests/*.cpp")
add_executable("run_test_reader" EXCLUDE_FROM_ALL ${TEST_FILES})
target_link_libraries("run_test_reader" gtest pthread READER)
add_dependencies(test_reader "run_test_reader")
add_test("reader_tests" "./reader_tests")
