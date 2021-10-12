cmake_minimum_required(VERSION 2.8)
project(Writer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

add_library(lib_writer file_writer.cpp)

# Setup testing
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/mock DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

link_directories(/usr/local/lib)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

file(GLOB TEST_FILES "tests/*.cpp")
#add_custom_target("build_test_writer" COMMAND GTEST_COLOR=yes ${CMAKE_CTEST_COMMAND} --verbose)
add_executable("test_writer" EXCLUDE_FROM_ALL ${TEST_FILES})
target_link_libraries("test_writer" gtest pthread lib_writer)
#add_dependencies(build_test_writer "test_writer")
add_test("test_writer" "./test_writer")
