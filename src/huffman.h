#ifndef HUFFMAN
#define HUFFMAN
#include "btree.h"
#include "heap.h"
#include <stdio.h>
void fill_tree(struct tree **tree, struct heap **queue);

void char_swap(char *first, char *second);  // Вот это, можно скрыть.

void get_code(struct tree *queue, char symbol, char *result);

int dict_write(struct tree *tree, FILE* fl);   // Запись частотного словаря в файл.

void insert_ready_node(struct tree **tree, struct node node);
#endif