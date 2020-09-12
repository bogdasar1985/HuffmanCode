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

	size_t j = 0; 		// Счётчик
	for(size_t i = 0; i < size_tmp-1; ++i)
	{
		struct node tmp;
		tmp.symbol = -1;
		tmp.frequency = (*tree)->array[j].frequency + (*tree)->array[j+1].frequency;

		(*tree)->array[(*tree)->size] = tmp;
		j+=2;
		(*tree)->size++;
	}

	// Это здесь скорее всего лишнее, но это не точно.
	for(int i = 0; i <= (int)(*tree)->size/2; ++i)
	{
		node_swap(&((*tree)->array[i]), &((*tree)->array[(*tree)->size-1-i]));
	}
}

void char_swap(char *first, char *second)
{
	char tmp = *first;
	*first = *second;
	*second = tmp;
}

void get_code(struct tree *queue, size_t index, char *result)	// Тут не нужен queue. LOL. Ну может только для обработки ошибок.
{
	size_t j = 0;
	while (index != 0)
	{
		if(index % 2 == 0)
		{
			*(result + j) = '1';
		}
		if(index % 2 != 0)
		{
			*(result + j) = '0';
		}
		j++;
		index = (index - 1) / 2;
	}

	for(int i = 0; i < (int)strlen(result) / 2; i++)
	{
		char_swap((result+i), (result+strlen(result)-i-1));
	}
}
