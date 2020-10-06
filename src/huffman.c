#include "huffman.h"
//Этот метод можно изменить и не нуждаться в перевороте в конце
void fill_tree(struct tree **tree, struct heap **queue)
{
    size_t i = 0;
    size_t size_tmp = (*queue)->size;
    while ((*queue)->size != 0)
    {
        (*tree)->array[i] = extract_min(queue);
        ++i;
    }

    (*tree)->size = size_tmp;

    size_t j = 0;
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

void get_code(struct tree *queue, char symbol, char *result)
{
	size_t index = 0;
	for(size_t i = 0; i < queue->size; ++i)
	{
		if(queue->array[i].symbol == symbol)
		{
			index = i;
			break;
		}
	}

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

	size_t size = strlen(result);
    for(size_t i = 0; i < size / 2; ++i)
	{
		char_swap((result+i), (result+size-i-1));
	}
}

int dict_write(struct tree *tree, FILE* fl)
{
	for(int i = 0; i < tree->size; ++i)
	{
		//Сейчас, он добавляет всё дерево, включая ноды без символов.
		fwrite(&(tree->array[i].symbol), sizeof(tree->array[i].symbol), 1, fl);
		fwrite(&(tree->array[i].frequency), sizeof(tree->array[i].frequency), 1, fl);
	}
	return 0;
}

void insert_ready_node(struct tree **tree, struct node node)
{	
	if((*tree)->size == (*tree)->capacity)
	{
		(*tree)->array = reallocarray((*tree)->array, (*tree)->size * 2, sizeof(struct node));
		(*tree)->capacity = (*tree)->capacity * 2;
	}
	(*tree)->size++;
	(*tree)->array[(*tree)->size - 1].symbol = node.symbol;
	(*tree)->array[(*tree)->size - 1].frequency = node.frequency;
}

struct node *get_symbol(struct tree *tree, char *code)
{
	if (tree == NULL || code == NULL)
	{
		return NULL;
	}
	
	size_t size = strlen(code);
	int pos = 0;
	
	for(size_t i = 0; i < size; ++i)
	{
		if(code[i] == '0')
		{
			pos = pos * 2 + 1;
		}
		if(code[i] == '1')
		{
			pos = pos * 2 + 2;
		}
		if((pos-1) > tree->size)
		{
			return NULL;
		}
	}
	if(tree->array[pos].symbol == -1)
	{
		return NULL;
	}
	else
	{
		return &(tree->array[pos]);
	}
}