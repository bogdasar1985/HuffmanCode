#include "btree.h"
void init_tree(struct heap **queue, struct tree **tree)
{
	(*tree) = malloc(sizeof(struct tree));
	(*tree)->array = calloc((*queue)->size + ((*queue)->size - 1), sizeof(struct node));
	size_t size_tmp = (*queue)->size;	//Данное значение меняется после exctract_min

	size_t i = 0;
	while((*queue)->size != 0)
	{
		(*tree)->array[i] = extract_min(queue);
		i++;
	}

	(*tree)->size = size_tmp;
	(*tree)->capacity = size_tmp + size_tmp - 1;

	size_t j = 0; // Счётчик
	for(size_t i = 0; i < size_tmp-1; i++)
	{
		struct node tmp;
		tmp.symbol = -1;
		tmp.frequency = (*tree)->array[j].frequency + (*tree)->array[j+1].frequency;
		(*tree)->array[(*tree)->size] = tmp;
		j+=2;
		(*tree)->size++;
	}
}