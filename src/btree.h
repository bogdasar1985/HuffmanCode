#ifndef BTREE
#define BTREE
#include <stdlib.h>
#include <string.h>
#include "node.h"
struct tree
{
    struct node *array;
    size_t capacity;
    size_t size;
};

void init_tree(struct tree **tree, size_t size);
#endif