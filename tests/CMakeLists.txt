cmake_minimum_required(VERSION 3.0)

project(Check VERSION 1.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "..")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "..")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "..")

link_directories(../src)

add_executable(main main.c)

target_link_libraries(main huffman check subunit pthread m rt)
