#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE
#include <stdlib.h>
#include <stdio.h>
struct pq_node {
    unsigned long frequency;
    struct pq_node *parent;
    struct pq_node *left;
    struct pq_node *right;
    char symbol;
};

struct priority_queue {
    struct pq_node **heap_on_array;
    size_t size;
    size_t capacity;
};

// Return 0 if all is OK, -1 if can't alloc pq and -2 if can't alloc pq->heap_on_array.
int pq_init(struct priority_queue **pq, size_t capacity);

void shift_up(struct priority_queue *pq, int i);

void shift_down(struct priority_queue *pq, size_t i);

struct pq_node *pq_extract_min(struct priority_queue *pq);

// Return position if find, or -1 if not.
int pq_find(struct priority_queue *pq, char symbol);

// Return 0 if all is OK, and -1 if we can't alloc memory.
int pq_insert_element(struct priority_queue *pq, char symbol, unsigned long frequency, struct pq_node *node);

void node_swap(struct pq_node **first, struct pq_node **second);

struct pq_node *tr_build(struct pq_node *first, struct pq_node *second);

// Recursive function, that find node with symbol in tree, and save adress of node in `res` argument.
// If can't find, `res` will not change.(?)
void tr_find_symbol(struct pq_node *tree, char symbol, struct pq_node **res);

void tr_get_code(struct pq_node *node, char *result);
#endif