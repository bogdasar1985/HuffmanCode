#include <sys/stat.h>
#include <limits.h>
#include <assert.h>
#include "huffman.h"
#define CODE_SIZE 256
int main(int argc, char *argv[])
{
    FILE *source_fl = NULL;
    FILE *result_fl = NULL;
    struct priority_queue *pq = NULL;
    char less_bits = 0;
    size_t pq_size = 0;
    char buf[BUFSIZ];
    char code[CODE_SIZE];
    struct stat stats;
    char ch;
    size_t pos = 0;
    size_t tmp_tr_size = 0;     // Переменная для запоминания размера очереди.

    if(argc < 3)
    {
        fprintf(stderr, "Too few arguments!\n");
        return 1;
    }
    
    source_fl = fopen(argv[1], "r+");
    if(source_fl == NULL)
    {
        return -1;
    }

    result_fl = fopen(argv[2], "w+");
    if(result_fl == NULL)
    {
        return -2;
    }

    fread(&less_bits, sizeof(char), 1, source_fl);
    fread(&pq_size, sizeof(pq_size), 1, source_fl);
    fread(&buf, pq_size, sizeof(char) + sizeof(unsigned long), source_fl);
    #ifdef DEBUG
    fprintf(stdout, "less_bits = %d , pq_size = %ld\n", less_bits, pq_size);
    #endif
    pq_init(&pq, pq_size);
    pq_fill_from_str(&pq, buf, pq_size);
    tmp_tr_size = pq->size;

    #ifdef DEBUG
    fprintf(stdout, "Queue: \n");
    for(size_t i = 0; i < pq->size; ++i)
    {
        fprintf(stdout, "Queue[%ld]: %c %ld\n", i, pq->heap_on_array[i]->symbol, pq->heap_on_array[i]->frequency);
    }
    #endif
    
    while (pq->size != 1)
    {
        struct pq_node *first = pq_extract_min(pq);
        struct pq_node *second = pq_extract_min(pq);
        struct pq_node *node = tr_build(first, second);
        pq_insert_element(pq, -1, 0, node);
    }
    #ifdef DEBUG
    print_tree(pq->heap_on_array[0]);
    fprintf(stdout, "\nStart reading...\n");
    #endif 
    fstat(fileno(source_fl), &stats);
    for(long i = ftell(source_fl); i < stats.st_size; ++i)
    {
        struct pq_node *tmp = NULL;
        fread(&ch, 1, 1, source_fl);
        if(i == stats.st_size - 1)
        {
            for(int i = CHAR_BIT-1; i >= less_bits; --i)
            {
                code[pos] = ((ch & (1 << i)) >> i) + '0';
                #ifdef DEBUG
                fprintf(stdout, "%c", code[pos]);
                #endif
                ++pos;
                if((tmp = tr_get_symbol(pq->heap_on_array[0], code, CODE_SIZE))->symbol != -1)
                {
                    #ifdef DEBUG
                    fprintf(stdout, "\nFind symbol: %c (%s)\n", tmp->symbol, code);
                    #endif
                    fwrite(&(tmp->symbol), 1, 1, result_fl);
                    memset(code, '\0', CODE_SIZE);
                    pos = 0;
                }
            }
        }
        else
        {
            for(int i = CHAR_BIT-1; i >= 0; --i)
            {
                code[pos] = ((ch & (1 << i)) >> i) + '0';
                #ifdef DEBUG
                fprintf(stdout, "%c", code[pos]);
                #endif
                ++pos;
                if((tmp = tr_get_symbol(pq->heap_on_array[0], code, CODE_SIZE))->symbol != -1)
                {
                    #ifdef DEBUG
                    fprintf(stdout, "\nFind symbol: %c (%s)\n", tmp->symbol, code);
                    #endif
                    fwrite(&(tmp->symbol), 1, 1, result_fl);
                    memset(code, '\0', CODE_SIZE);
                    pos = 0;
                }
            }
        }       
    }

    fclose(source_fl);
    fclose(result_fl);
    tr_free(pq->heap_on_array[0]);

    for(size_t i = pq->capacity - 1; i > tmp_tr_size-1; --i)
    {
        free(pq->heap_on_array[i]);
    }
    free(pq->heap_on_array);
    free(pq);
    return 0;
}