#include <stdio.h>
#include <sys/stat.h>
#include "utilities.h"
#include "huffman.h"
int main(int argc, char *argv[])
{
    FILE *fl = NULL;
    FILE *fl_write = NULL;
    struct tree *tree = NULL;
    char less_bits = 0;
    unsigned int dict_size = 0;
    unsigned int frequency = 0;
    char ch = '\0';
    char code[CHAR_BIT] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
    size_t pos = 0;
    struct stat stats;

    if((fl = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Can't open file!\n");
        return -1;
    }
    if((fl_write = fopen(argv[2], "w+")) == NULL)
    {
        fprintf(stderr, "Can't creat file!\n");
        return -2;
    }

    fread(&less_bits, sizeof(less_bits), 1, fl);
    fread(&dict_size, sizeof(dict_size), 1, fl);

    init_tree(&tree, dict_size + dict_size - 1);
    for(unsigned int i = 0; i < dict_size + dict_size - 1; ++i)
    {
        // Вставлять элемент в дерево.
        struct node tmp;
        fread(&(tmp.symbol), sizeof(tmp.symbol), 1, fl);
        fread(&(tmp.frequency), sizeof(tmp.frequency), 1, fl);
        insert_ready_node(&tree, tmp);
    }
    #ifdef DEBUG
    fprintf(stdout, "Less bits: %d\nDict size: %d\n", less_bits, dict_size);
    for(int i = 0; i < tree->size; ++i)
    {
        fprintf(stdout, "%c %d | ", tree->array[i].symbol, tree->array[i].frequency);
    }
    fprintf(stdout, "%c", '\n');
    #endif
    
    fstat(fileno(fl), &stats);
    for(long j = ftell(fl); j < stats.st_size; ++j)
    {
        struct node *tmp = NULL;
        fread(&ch, 1, 1, fl);
        #ifdef DEBUG
        fprintf(stdout, "Read byte: 0b");
        for(int i = CHAR_BIT - 1; i >= 0; --i)
        {
            fprintf(stdout, "%c", ((ch & (1 << i)) >> i) + '0');
        }
        fprintf(stdout, "%c", '\n');
        #endif
        if(j ==  stats.st_size - 1)
        {
            #ifdef DEBUG
            fprintf(stdout, "(last)\n");
            #endif
            for(int i = CHAR_BIT-1; i >= less_bits; --i)  //Тут проблема
            {
                // Считываем биты в массив
                code[pos] = ((ch & (1 << i)) >> i) + '0';
                ++pos;
                if((tmp = get_symbol(tree, code)) != NULL)
                {
                    fwrite(&(tmp->symbol), 1, 1, fl_write);
                    #ifdef DEBUG
                    fprintf(stdout, "Write symbol -->%c<-- with ASCII-code %d and HUffman code %s\n", tmp->symbol, tmp->symbol, code);
                    #endif
                    memset(code, '\0', CHAR_BIT);
                    pos = 0;
                }
            }
        }
        else
        {
            for(int i = CHAR_BIT-1; i >= 0; --i)
            {
                // Считываем биты в массив
                code[pos] = ((ch & (1 << i)) >> i) + '0';
                ++pos;
                if((tmp = get_symbol(tree, code)) != NULL)
                {
                    fwrite(&(tmp->symbol), 1, 1, fl_write);
                    #ifdef DEBUG
                    fprintf(stdout, "Write symbol -->%c<-- with ASCII-code %d and HUffman code %s\n", tmp->symbol, tmp->symbol, code);
                    #endif
                    memset(code, '\0', CHAR_BIT);
                    pos = 0;
                }
            }
        }
    }
    
    fclose(fl);
    fclose(fl_write);
}