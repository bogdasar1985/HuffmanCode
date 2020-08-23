#ifndef NODE
#define NODE
struct node
{
	unsigned long long counter;
	struct node *next;
	struct node *left;
	struct node *right;
	char symbol;
};
#endif
