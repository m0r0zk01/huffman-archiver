cmake_minimum_required(VERSION 2.8)
project(archiver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

add_executable(archiver.sh main.cpp)


if (NOT TARGET READER)
    add_subdirectory(./reader/)
endif()
if (NOT TARGET WRITER)
    add_subdirectory(./writer/)
endif()
if (NOT TARGET ARCHIVER)
    add_subdirectory(./archiver/)
endif()
if (NOT TARGET TRIE)
    add_subdirectory(./trie/)
endif()
if (NOT TARGET UTILS)
    add_subdirectory(./utils/)
endif()

target_link_libraries(archiver.sh ARCHIVER READER WRITER TRIE UTILS)

# Setup testing
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/mock DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

link_directories(/usr/local/lib)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

file(GLOB TEST_FILES "tests/*.cpp")
add_executable("test_all" EXCLUDE_FROM_ALL ${TEST_FILES})
target_link_libraries("test_all" gtest pthread ARCHIVER READER WRITER TRIE UTILS)
add_test("test_all" "test_all")

