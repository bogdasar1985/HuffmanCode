#include "huffman.h"
#include "utilities.h"
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
    struct heap *queue = NULL;
    struct tree *tree = NULL;
    FILE* fl = NULL;
    FILE* meta_fl = NULL;
    FILE* comp_fl = NULL;
    char ch = '\0';
    char wr_ch = '\0';
    char buf[BUFSIZ];
    char bit_counter = 0;  // Сколько бит записано.
    size_t bit_position = 7; // Первый бит байта, если читать слева.
    unsigned int heap_size = 0;   //Чтобы запомнить размер частотного словаря.

    if(argc < 3)
    {
        fprintf(stderr, "There are no file and compress file names!\n");
        return -1;
    }
    if((comp_fl = fopen(argv[2], "w+")) == NULL)
    {
        fprintf(stderr, "Can't create result file!\n");
        return -1;
    }
    if((fl = fopen(argv[1], "r+")) == NULL)
    {
        fprintf(stderr, "Wrong file name or program just can't open it!\n");
        return -2;
    }
    if((meta_fl = fopen(".metafile.txt", "w+")) == NULL)
    {
        fprintf(stderr, "Can't create tmp file!\n");
        return -3;
    }

    init_heap(&queue);
    while(fread(&ch, 1, 1, fl) != 0)
    {
        insert(&queue, ch);
    }

    init_tree(&tree, (queue->size) + (queue->size) + 1);
    heap_size = queue->size;     //Запоминаем размер.
    fill_tree(&tree, &queue);
    
    fseek(fl, 0, SEEK_SET);
    while(fread(&ch, 1, 1, fl) != 0)
    {
        get_code(tree, ch, buf);
        #ifdef DEBUG
        static unsigned long long _number = 0;
        ++_number;
        fprintf(stdout, "Log: read symbol №%lld -->%c<-- with ASCII-code %d and Huffman code %s from a file\n", _number, ch, ch, buf);
        #endif
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
                fwrite(&wr_ch, 1, 1, meta_fl);
                #ifdef DEBUG
                fprintf(stdout, "0b");
                for(int i = CHAR_BIT-1; i >= 0; --i)
                {
                    fprintf(stdout, "%c", ((wr_ch & (1 << i)) >> i) + '0');
                }
                fprintf(stdout, "%c", '\n');
                #endif
                bit_position = 7;
                bit_counter = 0;
                wr_ch = '\0';
            }
        }
        memset(buf, '\0', BUFSIZ);
    }
    // Вот тут дописываем оставшиеся биты
    if(bit_counter > 0)
    {
        fwrite(&wr_ch, 1, 1, meta_fl);
        #ifdef DEBUG
        fprintf(stdout, "Loss bits: 0b");
        for(int i = CHAR_BIT-1; i >= 0; --i)
        {
            fprintf(stdout, "%c", ((wr_ch & (1 << i)) >> i) + '0');
        }
        fprintf(stdout, "%c", '\n');
        #endif
    }

    // Переходим в начало файла.
    // TODO: информация будет затираться, чтобы этого избежать, надо использовать временный файл.
    fseek(comp_fl, 0, SEEK_SET);    
    // Тут пишем кол-во лишних бит (1 байт)
    if(bit_counter == 0)
    {
        fwrite(&bit_counter, sizeof(bit_counter), 1, comp_fl);
        #ifdef DEBUG
        fprintf(stdout, "Loss bits = %d\n", bit_counter);
        #endif
    }
    else
    {
        bit_counter = 8 - bit_counter;
        fwrite(&bit_counter, sizeof(bit_counter), 1, comp_fl);
        #ifdef DEBUG
        fprintf(stdout, "Loss bits = %d\n", bit_counter);
        #endif
    }
    
    // Пишем длину дерева в файл
    fwrite(&heap_size, sizeof(heap_size), 1, comp_fl);
    
    dict_write(tree, comp_fl);  //Записывает всё дерево.
    #ifdef DEBUG
    fprintf(stdout, "Tree: \n");
    for(int i = 0; i < tree->size; ++i)
    {
        fprintf(stdout, "%c %d | ", tree->array[i].symbol, tree->array[i].frequency);
    }
    #endif
    fseek(meta_fl, 0, SEEK_SET);
    while (fread(&ch, 1, 1, meta_fl) != 0)
    {
        fwrite(&ch, sizeof(ch), 1, comp_fl);
    }
    
    remove(".metafile.txt");
    fclose(fl);
    fclose(meta_fl);
    fclose(comp_fl);
    free(tree->array);
    free(tree);
    free(queue->array);
    free(queue);
}
