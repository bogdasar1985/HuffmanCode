cmake_minimum_required(VERSION 3.0)

project(Huffman VERSION 1.0)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g3 -Wall -Wextra -Wconversion -pedantic")

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wconversion -pedantic")

add_definitions("-Wall -Wextra -Wconversion -pedantic -DDEBUG")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "..")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "..")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "..")

add_library(huffman SHARED huffman.h huffman.c)

add_executable(coder coder.c)

target_link_libraries(coder huffman)