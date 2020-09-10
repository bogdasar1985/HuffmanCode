#ifndef NODE
#define NODE
struct node
{
    unsigned long long frequency;
    char symbol;
};

void node_swap(struct node *first, struct node *second);
#endif
