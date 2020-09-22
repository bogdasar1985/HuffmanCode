#include "huffman.h"
#include "utilities.h"
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
    struct heap *heap = NULL;
    struct tree *tree = NULL;
    FILE* fl = NULL;
    FILE* comp_fl = NULL;
    FILE* meta_fl = fopen(".metainfo.txt", "w+");
    char ch = 0x0;
    char wr_ch = 0x0;
    char buf[BUFSIZ];
    size_t bit_counter = 0;  // Сколько бит записано.
    size_t bit_position = 7; // Первый бит байта, если читать слева.
    size_t heap_size = 0;   //Чтобы запомнить размер частотного словаря.

    if(argc < 3)
    {
        fprintf(stderr, "There are no file and compress file names!\n");
        return -1;
    }
    if((fl = fopen(argv[1], "r+")) == NULL)
    {
        fprintf(stderr, "Wrong file name or program just can't open it!\n");
        return -2;
    }
    if((comp_fl = fopen(argv[2], "w+")) == NULL)
    {
        fprintf(stderr, "Can't create a file! Maybe you miss an argument!\n");
        return -3;
    }

    init_heap(&heap);

    while(fread(&ch, 1, 1, fl) != 0)
    {
        insert(&heap, ch);
    }

    init_tree(&tree, (heap->size) + (heap->size) + 1);
    heap_size = heap->size;     //Запоминаем размер.
    fill_tree(&tree, &heap);
    
    fseek(fl, 0, SEEK_SET);
    
    // Обработать пограничные ситуации.
    // 1. Ситуация, записи последнего символа:
    // 1.1 Посчитать разницу между 8 и длиной кода символа.
    //     Записать эту информацию в начало файла.
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
                fwrite(&wr_ch, 1, 1, comp_fl);    //TODO: Заменить на ввод в файл.
                bit_position = 7;
                bit_counter = 0;
                wr_ch = 0x0;
            }
        }
        memset(buf, '\0', BUFSIZ);
    }

    // ЭТО ВСЁ ПСЕВДОКОД!
    // Вот тут дописываем оставшиеся биты
    if(bit_counter > 0)
    {
        fwrite(&wr_ch, 1, 1, comp_fl);
    }

    // Переходим в начало файла.
    // TODO: информация будет затираться, чтобы этого избежать, надо использовать временный файл.
    fseek(meta_fl, 0, SEEK_SET);
    
    // Тут пишем кол-во лишних бит (1 байт)
    if(bit_counter == 0)
    {
        ch = bit_counter + '0';         // int to char
        fwrite(&ch, sizeof(ch), 1, meta_fl);
    }
    else
    {
        bit_counter = 8 - bit_counter;
        ch = bit_counter + '0';         // int to char
        fwrite(&ch, sizeof(ch), 1, meta_fl);
    }
    
    // Пишем длину дерева в файл (3 байта?), предварительно, переведя в строку
    memset(buf, '\0', BUFSIZ);
    to_string(buf, 3, heap_size);
    fwrite(buf, 3, 1, meta_fl);
    dict_write(tree, meta_fl);

    fseek(comp_fl, 0, SEEK_SET);
    while (fread(&ch, 1, 1, comp_fl) != 0)
    {
        fwrite(&ch, sizeof(ch), 1, meta_fl);
    }
    
    fclose(fl);
    free(tree->array);
    free(tree);
    free(heap->array);
    free(heap);
}
