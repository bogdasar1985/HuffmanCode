#include "huffman.h"
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
    struct heap *heap = NULL;
    struct tree *tree = NULL;
    FILE* fl = NULL;
    char ch = 0x0;
    char wr_ch = 0x0;
    char buf[BUFSIZ];
    size_t bit_counter = 0;  // Сколько бит записано.
    size_t bit_position = 7; // Первый бит байта, если читать слева.

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

    init_tree(&tree, (heap->size) + (heap->size) + 1);
    fill_tree(&tree, &heap);
    
    fseek(fl, 0, SEEK_SET);
    
    // Обработать пограничные ситуации.
    while(fread(&ch, 1, 1, fl) != 0)
    {
        get_code(tree, ch, buf);
        for(size_t i = 0; i < strlen(buf); ++i)
        {
            if(buf[i] == '0')
            {
                wr_ch &= ~(1UL << bit_position);
            }
            if(buf[i] == '1')
            {
                wr_ch |= 1UL << bit_position;
            }
            ++bit_counter;
            --bit_position;
            if(bit_counter == 8)
            {
                printf("%c", wr_ch);    //TODO: Заменить на ввод в файл.
                bit_position = 7;
                bit_counter = 0;
                wr_ch = 0x0;
            }
        }
        memset(buf, '\0', BUFSIZ);
    }

    fclose(fl);
    free(tree->array);
    free(tree);
    free(heap->array);
    free(heap);
}
