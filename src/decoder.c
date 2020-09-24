#include <stdio.h>
#include "huffman.h"
int main(int argc, char *argv[])
{
    FILE *fl = NULL;
    struct tree *tree = NULL;
    char less_bits = 0;
    unsigned int dict_size = 0;
    unsigned int frequency = 0;
    char ch = 0x0;

    if((fl = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Can't open file!\n");
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
}