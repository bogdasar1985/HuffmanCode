#include "heap.h"
void init_heap(struct heap **heap)
{
	(*heap) = malloc(sizeof(struct heap));
	(*heap)->array = malloc(sizeof(struct node));
	(*heap)->capacity = 1;
	(*heap)->size = 0;
};

void shift_up(struct heap **heap, int i)
{
	while ((*heap)->array[i].frequency < (*heap)->array[(i-1)/2].frequency)
	{
		node_swap(&((*heap)->array[i]), &((*heap)->array[(i-1)/2]));
		i = (i - 1) / 2;
	}
}

void shift_down(struct heap **heap, size_t i)
{
	while ((2 * i + 1) < (*heap)->size)
	{
		size_t left = 2 * i + 1;
		size_t right = 2 * i + 2;
		size_t j = left;
		if((right < (*heap)->size) && ((*heap)->array[right].frequency < (*heap)->array[left].frequency))
		{
			j = right;
		}
		if((*heap)->array[i].frequency <= (*heap)->array[j].frequency)
		{
			break;
		}
		node_swap(&((*heap)->array[i]), &((*heap)->array[j]));
		i = j;
	}
}

struct node extract_min(struct heap **heap)
{
	struct node tmp = (*heap)->array[0];
	(*heap)->array[0] = (*heap)->array[(*heap)->size - 1];
	(*heap)->size--;
	shift_down(heap, 0);
	return tmp;
}

void insert(struct heap **heap, char symbol)
{
	for(size_t i = 0; i < (*heap)->size; i++)
	{
		if((*heap)->array[i].symbol == symbol)
		{
			(*heap)->array[i].frequency++;
			shift_down(heap, i);
			return;
		}
	}
	
	if((*heap)->size == (*heap)->capacity)
	{
		(*heap)->array = reallocarray((*heap)->array, (*heap)->size * 2, sizeof(struct node));
		(*heap)->capacity = (*heap)->capacity * 2;
	}
	(*heap)->size++;
	(*heap)->array[(*heap)->size - 1].symbol = symbol;
	(*heap)->array[(*heap)->size - 1].frequency = 1;
	shift_up(heap, (*heap)->size - 1);
}