#include "huffman.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>
int main(int argc, char *argv[])
{
    FILE *source_fl = NULL;
    FILE *result_fl = NULL;
    struct priority_queue *pq = NULL;
    struct priority_queue *pq_tmp = NULL;
    char symbol;
    char bits = '\0';
    char result[BUFSIZ] = {'\0'};
    char bit_counter = 0;
    size_t bit_position = 7;
    struct pq_node *tmp = NULL; 
    size_t tmp_tr_size = 0;     // Remember the queue size. (That is for free memory. :-/)

    if(argc < 3)
    {
        fprintf(stderr, "Too few arguments!\n");
        return 1;
    }

    source_fl = fopen(argv[1], "r+");
    if(source_fl == NULL)
    {
        return 2;
    }

    result_fl = fopen(argv[2], "w+");
    if(result_fl == NULL)
    {
        return 3;
    }

    pq_init(&pq, 1);
    
    while(fread(&symbol, 1, 1, source_fl) != 0)
    {
        pq_insert_element(pq, symbol, 1, NULL);
    }

    pq_init(&pq_tmp, pq->size);
    pq_fill_from_pq(&pq_tmp, pq);
    tmp_tr_size = pq->size;

    while (pq->size != 1)
    {
        struct pq_node *first = pq_extract_min(pq);
        struct pq_node *second = pq_extract_min(pq);
        struct pq_node *node = tr_build(first, second);
        pq_insert_element(pq, -1, 0, node);
    }

    // On this pass, we do not write anything, we just get the number of extra bits.
    fseek(source_fl, 0, SEEK_SET);
    while(fread(&symbol, 1, 1, source_fl) != 0)
    {
        tr_find_symbol(pq->heap_on_array[0], symbol, &tmp);
        tr_get_code(tmp, result);
        size_t size = strlen(result);
        for(size_t i = 0; i < size; ++i)
        {
            if(result[i] == '0')
            {
                bits &= (char)~(1UL << bit_position);
            }
            if(result[i] == '1')
            {
                bits |= (char)(1UL << bit_position);
            }
            ++bit_counter;
            --bit_position;
            if(bit_counter == 8)
            {
                bit_position = 7;
                bit_counter = 0;
                bits = '\0';
            }
        }
        memset(result, '\0', BUFSIZ);
    }

    if(bit_counter != 0)
    {
        bit_counter = 8 - bit_counter;
    }

    fwrite(&bit_counter, sizeof(bit_counter), 1, result_fl);   // Writing info about less_bits
    fwrite(&(pq_tmp->size), sizeof(pq_tmp->size), 1, result_fl); // Writing info about queue size

    // Queue writing
    for(size_t i = 0; i < pq_tmp->size; ++i)
    {
        fwrite(&(pq_tmp->heap_on_array[i]->symbol), sizeof(pq_tmp->heap_on_array[i]->symbol), 1, result_fl);
        fwrite(&(pq_tmp->heap_on_array[i]->frequency), sizeof(pq_tmp->heap_on_array[i]->frequency), 1, result_fl);
    }

    bit_counter = 0;
    bit_position = 7;
    bits = '\0';

    fseek(source_fl, 0, SEEK_SET);
    while(fread(&symbol, 1, 1, source_fl) != 0)
    {
        tr_find_symbol(pq->heap_on_array[0], symbol, &tmp);
        tr_get_code(tmp, result);
        size_t size = strlen(result);
        for(size_t i = 0; i < size; ++i)
        {
            if(result[i] == '0')
            {
                bits &= (char)(~(1UL << bit_position));
            }
            if(result[i] == '1')
            {
                bits |= (char)(1UL << bit_position);
            }
            ++bit_counter;
            --bit_position;
            if(bit_counter == 8)
            {
                fwrite(&bits, sizeof(bits), 1, result_fl);
                bit_position = 7;
                bit_counter = 0;
                bits = '\0';
            }
        }
        memset(result, '\0', BUFSIZ);
    }

    // Writing extra bits
    if(bit_counter > 0)
    {
        fwrite(&bits, 1, 1, result_fl);
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

    for(size_t i = pq_tmp->capacity - 1; i > 0; --i)
    {
        free(pq_tmp->heap_on_array[i]);
    }
    free(*(pq_tmp->heap_on_array));
    free(pq_tmp->heap_on_array);
    free(pq_tmp);
    return 0;
}