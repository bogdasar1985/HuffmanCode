cmake_minimum_required(VERSION 3.0)

project(Huffman VERSION 1.0)

add_library(node OBJECT node.h node.c)

add_library(heap OBJECT heap.h heap.c)

add_library(btree OBJECT btree.h btree.c)

add_library(huffman OBJECT huffman.h huffman.c)

add_executable(main main3.c)

target_link_libraries(main node heap btree huffman)
