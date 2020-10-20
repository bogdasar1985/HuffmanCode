// Надо делать в 2 прохода, на первом получаем метаинформацию, на втором пишем в файл.
#include "huffman.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>
int main(int argc, char *argv[])
{
    FILE *source_fl = NULL;
    FILE *result_fl = NULL;
    struct priority_queue *pq = NULL;
    struct priority_queue *pq_tmp = NULL; // Это очередь, из которой мы скопируем её в файл.
    char symbol;
    char bits = '\0';
    char result[10] = {'\0'};
    char bit_counter = 0;  // Сколько бит записано.
    size_t bit_position = 7; // Первый бит байта, если читать слева.
    struct pq_node *tmp = malloc(sizeof(struct pq_node));

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

    pq_init(&pq, 1);
    
    while(fread(&symbol, 1, 1, source_fl) != 0)
    {
        pq_insert_element(pq, symbol, 1, NULL);
    }

    // Копирование очереди.
    pq_init(&pq_tmp, pq->size);
    pq_fill_from_pq(&pq_tmp, pq);

    while (pq->size != 1)
    {
        struct pq_node *first = pq_extract_min(pq);
        struct pq_node *second = pq_extract_min(pq);
        struct pq_node *node = tr_build(first, second);
        pq_insert_element(pq, -1, 0, node);
    }

    // Это холостой проход, он ничего не записывает. Тут мы получаем кол-во лишних бит(bit_counter).
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
                bits &= ~(1UL << bit_position);
            }
            if(result[i] == '1')
            {
                bits |= 1UL << bit_position;
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
        memset(result, '\0', 10);
    }

    //printf("%d\n", 8 - bit_counter);
    //printf("%ld\n", pq_tmp->size);
    if(bit_counter != 0)
    {
        bit_counter = 8 - bit_counter;
    }

    fwrite(&bit_counter, sizeof(bit_counter), 1, result_fl);   // Запись инфы о лишних битах
    fwrite(&(pq_tmp->size), sizeof(pq_tmp->size), 1, result_fl); // Запись инфы о длине очереди

    // Запись очереди
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
                bits &= ~(1UL << bit_position);
            }
            if(result[i] == '1')
            {
                bits |= 1UL << bit_position;
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
        memset(result, '\0', 10);
    }

    // Записываем оставшиеся биты
    if(bit_counter > 0)
    {
        fwrite(&bits, 1, 1, result_fl);
    }
    return 0;
}