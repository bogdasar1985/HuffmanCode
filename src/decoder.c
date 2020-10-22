#include "huffman.h"
int main(int argc, char *argv[])
{
    FILE *source_fl = NULL;
    FILE *result_fl = NULL;
    struct priority_queue *pq = NULL;
    char less_bits = 0;
    size_t pq_size = 0;
    char buf[BUFSIZ];

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

    pq_init(&pq, pq_size);
    pq_fill_from_str(&pq, buf, pq->size);
    return 0;
}