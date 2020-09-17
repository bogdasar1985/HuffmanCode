cmake_minimum_required(VERSION 3.0)

project(Tests VERSION 1.0)

link_directories(../src)

add_executable(main main.c)

target_link_libraries(main heap btree huffman check subunit pthread m rt)
