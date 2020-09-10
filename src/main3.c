#include "heap.h"
#include "btree.h"
#include <stdio.h>
int main()
{
    struct heap *heap = NULL;
    struct tree *tree = NULL;
    init_heap(&heap);
    for(size_t i = 0; i < 5;  i++)
    {
        insert(&heap, 'a');
    }
    for(size_t i = 0; i < 2;  i++)
    {
        insert(&heap, 'b');
    }
    for(size_t i = 0; i < 8;  i++)
    {
        insert(&heap, 'c');
    }
    for(size_t i = 0; i < 16;  i++)
    {
        insert(&heap, 'x');
    }
    for(size_t i = 0; i < 1;  i++)
    {
        insert(&heap, 'd');
    }
    for(size_t i = 0; i < 6;  i++)
    {
        insert(&heap, 'q');
    }
    for(size_t i = 0; i < 26;  i++)
    {
        insert(&heap, 's');
    }
    for(size_t i = 0; i < 6;  i++)
    {
        insert(&heap, 'q');
    }
    
    init_tree(&heap, &tree); //Вроде работает. Дерево с конца читать.

    for(size_t i = tree->size - 1; i > 0; i--)
    {
        printf("%lld %c\n", tree->array[i].frequency, tree->array[i].symbol);
    }
    
    free(tree->array);
    free(tree);
    free(heap->array);
    free(heap);
}
