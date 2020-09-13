#include "btree.h"
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
    struct heap *heap = NULL;
    struct tree *tree = NULL;
    FILE* fl = NULL;
    char ch = 0x0;
    char buf[BUFSIZ];

    if(argc < 2)
    {
        fprintf(stderr, "There are no file name!\n");
        return -1;
    }
    if((fl = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Wrong file name or program just can't open it!\n");
        return -2;
    }

    init_heap(&heap);
    
    while(fread(&ch, 1, 1, fl) != 0)
    {
        insert(&heap, ch);
    }
    fclose(fl);

    init_tree(&heap, &tree); //Вроде работает. Дерево с конца читать.
    
    for(size_t i = 0; i < tree->size ; ++i)
    {
        if(tree->array[i].symbol != -1)
        {
            get_code(NULL, i, buf);
            printf("%c %s\n", tree->array[i].symbol, buf);
            memset(buf, '\0', BUFSIZ);
        }
    }

    free(tree->array);
    free(tree);
    free(heap->array);
    free(heap);
}
