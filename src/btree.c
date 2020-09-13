#include "btree.h"
void init_tree(struct tree **tree, size_t size)
{
	(*tree) = malloc(sizeof(struct tree));
	(*tree)->array = calloc(size, sizeof(struct node));
	(*tree)->size = 0;
	(*tree)->capacity = size;
}
