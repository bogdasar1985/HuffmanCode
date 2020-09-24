#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE
#include <stdlib.h>
#include "node.h"
struct heap
{
    struct node *array;
    unsigned int capacity;
    unsigned int size;
};

void init_heap(struct heap **heap);

void shift_up(struct heap **heap, int i);

void shift_down(struct heap **heap, size_t i);

struct node extract_min(struct heap **heap);

void insert(struct heap **heap, char symbol);
#endif