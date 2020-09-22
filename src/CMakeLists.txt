cmake_minimum_required(VERSION 3.0)

project(Huffman VERSION 1.0)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g3 -Wall -Wextra")

set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -Wextra")

add_library(utilities SHARED utilities.h utilities.c)

add_library(heap SHARED node.h node.c heap.h heap.c)

add_library(btree SHARED btree.h btree.c)   

add_library(huffman SHARED huffman.h huffman.c)

add_executable(main main3.c)

target_link_libraries(main heap btree huffman utilities)
