#include "huffman.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>
int main()
{
    struct priority_queue *pq = NULL;
    char code[32] = {'\0'};
    struct pq_node *res = NULL;

    pq_init(&pq, 1);

    while (pq->size > 1)
    {
        struct pq_node *tmp1 = pq_extract_min(pq);
        struct pq_node *tmp2 = pq_extract_min(pq);
        struct pq_node *tmp3 = tr_build(tmp1, tmp2);
        pq_insert_element(pq, -1, 0, tmp3);
    }
    
    return 0;
}