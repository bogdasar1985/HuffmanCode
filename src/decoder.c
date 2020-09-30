#include <stdio.h>
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
    char ch = 0x0;
    char code[CHAR_BIT] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
    size_t pos = 0;

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
    /***
    #ifdef DEBUG
    fprintf(stdout, "Start logging in get_bit loop.\n");
    fprintf(stdout, "loop counter | bit | is_symbol.\n");
    fprintf(stdout, "   symbol | ASCII-code | huffman code.\n\n");
    #endif
    while ((ch = getb(fl)) != EOF) // Не учитывается кол-во лишних бит! Короче, тут ошибка.
    {
        struct node *tmp = NULL;
        code[pos] = ch;
        ++pos;
        #ifdef DEBUG
        char symbol = 0x0;
        struct node *_tmp = NULL;
        if((tmp = get_symbol(tree, code)) != NULL)
        {
            symbol = tmp->symbol;
        }
        else
        {
            symbol = -1;
        }
        static unsigned long long _counter = 0;
        ++_counter;
        fprintf(stdout, "%lld | %c | %d\n", _counter, ch, symbol);
        #endif
        if((tmp = get_symbol(tree, code)) != NULL)
        {
            #ifdef DEBUG
            fprintf(stdout, "   %c | %d | %s\n", tmp->symbol, tmp->symbol, code);
            #endif
            fwrite(&(tmp->symbol), 1, 1, fl_write);
            memset(code, '\0', CHAR_BIT);
            pos = 0;
        }
    }
    */
    
    while(fread(&ch, 1, 1, fl) != 0)
    {
        struct node *tmp = NULL;
        for(int i = CHAR_BIT-1; i >= 0; --i)
        {
            // Считываем биты в массив
            code[pos] = ((ch & (1 << i)) >> i) + '0';
            ++pos;
            #ifdef DEBUG
            fprintf(stdout, "Get bit %d to code. Code is %s\n", code[pos-1], code);
            #endif
            if((tmp = get_symbol(tree, code)) != NULL)
            {
                #ifdef DEBUG
                fprintf(stdout, "   Code %s is a symbol -->%c<--\n", code, tmp->symbol);
                #endif
                fwrite(&(tmp->symbol), 1, 1, fl_write);
                memset(code, '\0', CHAR_BIT);
                pos = 0;
            }
        }
    }
    
    fclose(fl);
    fclose(fl_write);
}