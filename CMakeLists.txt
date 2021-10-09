cmake_minimum_required(VERSION 2.8)
project(archiver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

add_executable(archiver.sh main.cpp)

add_subdirectory(./reader/)
add_subdirectory(./writer/)
add_subdirectory(./archiver/)
add_subdirectory(./trie/)
add_subdirectory(./utils/)
add_subdirectory(./priority_queue)

target_link_libraries(archiver.sh lib_archiver lib_reader lib_writer lib_trie lib_utils)

# Setup testing
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/mock DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

link_directories(/usr/local/lib)

enable_testing()

add_custom_target("test_all")
add_test("test_all" run_test_archiver run_test_writer run_test_reader run_test_priority_queue)

