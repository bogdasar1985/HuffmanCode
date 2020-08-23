#include "btree.h"
struct node *merge(struct node *first, struct node *second)
{
	struct node *res = malloc(sizeof(struct node));
	if(first->counter < second->counter)
	{
		res->left = first;
		res->right = second;
	}
	else
	{
		res->right = first;
		res->left = second;
	}
	res->counter = first->counter + second->counter;
	res->symbol = -1;

	return res;
}
