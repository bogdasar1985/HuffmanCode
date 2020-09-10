#include "node.h"
void node_swap(struct node *first, struct node *second)
{
    struct node tmp = *first;
	*first = *second;
	*second = tmp;
}