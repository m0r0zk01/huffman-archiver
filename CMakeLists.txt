cmake_minimum_required(VERSION 2.8)
project(archiver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

add_executable(archiver.sh main.cpp)

add_subdirectory(./reader/)
add_subdirectory(./writer/)
add_subdirectory(./archiver/)
add_subdirectory(./binary_trie/)
add_subdirectory(./utils/)

target_link_libraries(archiver.sh lib_archiver lib_reader lib_writer lib_binary_trie lib_utils)

# Setup testing
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/mock DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

link_directories(/usr/local/lib)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

set(TESTS_FOLDER "tests")

add_executable("test_reader" ${TESTS_FOLDER}/reader_tests.cpp)
target_link_libraries("test_reader" gtest pthread lib_reader)
add_test("test_reader" "./test_reader")

add_executable("test_writer" ${TESTS_FOLDER}/writer_tests.cpp)
target_link_libraries("test_writer" gtest pthread lib_writer)
add_test("test_writer" "./test_writer")

add_executable("test_priority_queue" ${TESTS_FOLDER}/priority_queue_tests.cpp)
target_link_libraries("test_priority_queue" gtest pthread)
add_test("test_priority_queue" "./test_priority_queue")

add_executable("test_archiver" ${TESTS_FOLDER}/archiver_tests.cpp)
target_link_libraries("test_archiver" gtest pthread lib_archiver lib_utils lib_reader lib_writer lib_binary_trie)
add_test("test_archiver" "./test_archiver")

add_custom_target(test_all COMMAND test_archiver COMMAND test_priority_queue COMMAND test_writer COMMAND test_reader)
add_test("test_all" "./test_all")