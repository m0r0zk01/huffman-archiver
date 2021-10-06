cmake_minimum_required(VERSION 2.8)
project(Writer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

add_library(WRITER writer.cpp)

# Setup testing
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/mock DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

link_directories(/usr/local/lib)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_custom_target(test_writer COMMAND GTEST_COLOR=yes ${CMAKE_CTEST_COMMAND} --verbose)

file(GLOB TEST_FILES "tests/*.cpp")
add_executable("run_test_writer" EXCLUDE_FROM_ALL ${TEST_FILES})
target_link_libraries("run_test_writer" gtest pthread WRITER)
add_dependencies(test_writer "run_test_writer")
add_test("writer_tests" "./writer_tests")