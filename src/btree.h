#ifndef BTREE
#define BTREE
#include <stdlib.h>
#include "heap.h"
#include "node.h"
struct tree
{
    struct node *array;
    size_t capacity;
    size_t size;
};

void init_tree(struct heap **queue, struct tree **tree);
#endif