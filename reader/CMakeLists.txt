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

file(GLOB TEST_FILES "tests/*.cpp")
add_executable("test_reader" EXCLUDE_FROM_ALL ${TEST_FILES})
target_link_libraries("test_reader" gtest pthread READER)
add_dependencies(test_reader test_reader)
add_test("test_reader" "test_reader")
