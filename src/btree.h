#ifndef BTREE
#define BTREE
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "node.h"
struct tree
{
    struct node *array;
    size_t capacity;
    size_t size;
};

void init_tree(struct heap **queue, struct tree **tree);

void char_swap(char *first, char *second);

void get_code(struct tree *queue, size_t index, char *result);

#endif