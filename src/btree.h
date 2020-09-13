#ifndef BTREE
#define BTREE
#include <stdlib.h>
#include <string.h>
#include "node.h"
// Это определение структуры. Хули оно тут делает?
// Нельзя так блять! Нарушение инкапсуляции.
struct tree
{
    struct node *array;
    size_t capacity;
    size_t size;
};

void init_tree(struct tree **tree, size_t size);
#endif