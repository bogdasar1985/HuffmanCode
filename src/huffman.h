#ifndef HUFFMAN
#define HUFFMAN
#include "btree.h"
#include "heap.h"
void fill_tree(struct tree **tree, struct heap **queue);

void char_swap(char *first, char *second);  // Вот это, можно скрыть.

void get_code(struct tree *queue, size_t index, char *result);
#endif