#include "huffman.h"
int pq_init(struct priority_queue **pq, size_t capacity)
{
	(*pq) = malloc(sizeof(struct priority_queue));
	if((*pq) == NULL)
	{
		return -1;
	}

	(*pq)->heap_on_array = malloc(sizeof(struct pq_node) * capacity);
	if((*pq)->heap_on_array == NULL)
	{
		return -2;
	}

	for(size_t i = 0; i < capacity; ++i)
	{
		(*pq)->heap_on_array[i] = malloc(sizeof(struct pq_node));
	}
	
	(*pq)->capacity = capacity;
	(*pq)->size = 0;
	return (int)(capacity * sizeof(struct pq_node));
}

int pq_fill_from_str(struct priority_queue **pq, char *str, size_t size)
{
	size_t j = 0;
	if((*pq) == NULL)
	{
		return -1;
	}
	if(str == NULL)
	{
		return -2;
	}
	if((*pq)->capacity < size)
	{
		return -3;
	}
	for(size_t i = 0; i < size; ++i)
	{
		(*pq)->heap_on_array[i]->symbol = (char)str[j];
		j += sizeof(char);
		(*pq)->heap_on_array[i]->frequency = (unsigned long)str[j];
		j += sizeof(unsigned long);
		(*pq)->size++;
	}
	return (int)size;
}

int pq_fill_from_pq(struct priority_queue **pq, struct priority_queue *pq_intializer)
{
	if((*pq) == NULL)
	{
		return -1;	
	}
	if(pq == NULL)
	{
		return -2;
	}
	if((*pq)->capacity < pq_intializer->size)
	{
		return -3;
	}

	for(size_t i = 0; i < pq_intializer->size; ++i)
	{
		(*pq)->heap_on_array[i]->frequency = pq_intializer->heap_on_array[i]->frequency;
		(*pq)->heap_on_array[i]->left = pq_intializer->heap_on_array[i]->left;
		(*pq)->heap_on_array[i]->parent = pq_intializer->heap_on_array[i]->parent;
		(*pq)->heap_on_array[i]->right = pq_intializer->heap_on_array[i]->right;
		(*pq)->heap_on_array[i]->symbol = pq_intializer->heap_on_array[i]->symbol;
		(*pq)->size++;
	}
	return (int)(pq_intializer->size);
}

void shift_up(struct priority_queue *pq, int i)
{
	while (pq->heap_on_array[i]->frequency < pq->heap_on_array[(i-1)/2]->frequency)
	{
		node_swap(&(pq->heap_on_array[i]), &(pq->heap_on_array[(i-1)/2]));
		i = (i - 1) / 2;
	}
}

void shift_down(struct priority_queue *pq, size_t i)
{
	while ((2 * i + 1) < pq->size)
	{
		size_t left = 2 * i + 1;
		size_t right = 2 * i + 2;
		size_t j = left;
		if((right < pq->size) && (pq->heap_on_array[right]->frequency < pq->heap_on_array[left]->frequency))
		{
			j = right;
		}
		if(pq->heap_on_array[i]->frequency <= pq->heap_on_array[j]->frequency)
		{
			break;
		}
		node_swap(&(pq->heap_on_array[i]), &(pq->heap_on_array[j]));
		i = j;
	}
}

struct pq_node *pq_extract_min(struct priority_queue *pq)
{
	struct pq_node *tmp = pq->heap_on_array[0];

	pq->heap_on_array[0] = pq->heap_on_array[pq->size - 1];
	pq->size--;
	shift_down(pq, 0);	// Проблема здесь
	return tmp;
}

int pq_find(struct priority_queue *pq, char symbol)
{
	for(size_t i = 0; i < pq->size; ++i)
	{
		if(pq->heap_on_array[i]->symbol == symbol)
		{
			return (int)i;
		}
	}
	return -1;
}

int pq_insert_element(struct priority_queue *pq, char symbol, unsigned long frequency, struct pq_node *node)
{
	int pos = 0;
	if(((pos = pq_find(pq, symbol)) != -1) && (node == NULL))
	{
		pq->heap_on_array[pos]->frequency+=frequency;
		shift_down(pq, pos);
		return 0;
	}

    if(pq->size == pq->capacity)
	{
		pq->heap_on_array = reallocarray(pq->heap_on_array, pq->size * 2, sizeof(struct pq_node*));
		if(pq->heap_on_array == NULL)
		{
			return -1;
		}
		pq->capacity = pq->capacity * 2;
		for(size_t i = pq->size; i < pq->capacity; ++i)
		{
			pq->heap_on_array[i] = malloc(sizeof(struct pq_node));
		}
	}

	pq->size++;
	if(node == NULL)
	{
		pq->heap_on_array[pq->size - 1]->symbol = symbol;
		pq->heap_on_array[pq->size - 1]->frequency = frequency;
		pq->heap_on_array[pq->size - 1]->left = NULL;
		pq->heap_on_array[pq->size - 1]->right = NULL;
		pq->heap_on_array[pq->size - 1]->parent = NULL;
	}
	else
	{
		pq->heap_on_array[pq->size - 1] = node;	// Здесь node->paret == NULL. Вот.
	}
	shift_up(pq, pq->size - 1);
	return 0;
}

void node_swap(struct pq_node **first, struct pq_node **second)	// Вроде тут ошибка
{
    struct pq_node *tmp = *first;
	*first = *second;
	*second = tmp;
}

struct pq_node *tr_build(struct pq_node *first, struct pq_node *second)
{
	struct pq_node *tmp = malloc(sizeof(struct pq_node));
	if(tmp == NULL)
	{
		return NULL;
	}

	if(first == NULL || second == NULL)
	{
		return NULL;
	}

	first->parent = tmp;
	second->parent = tmp;

	if(first->frequency <= second->frequency)
	{
		tmp->left = first;
		tmp->right = second;
	}
	else
	{
		tmp->left = second;
		tmp->right = first;
	}

	tmp->parent = NULL;
	tmp->frequency = first->frequency + second->frequency;
	tmp->symbol = -1;
	return tmp;
}

void tr_find_symbol(struct pq_node *tree, char symbol, struct pq_node **res)
{
	if(tree == NULL)
	{
		return;
	}
	tr_find_symbol(tree->left, symbol, res);
	if(tree->symbol == symbol)
	{
		*res = tree;
	}
	tr_find_symbol(tree->right, symbol, res);
}

void tr_get_code(struct pq_node *node, char *result)
{
	size_t pos = 0;
	struct pq_node *tmp = NULL;

	while(node->parent != NULL)	// node->parent
	{
		tmp = node;
		node = node->parent;
		if(node->left == tmp)
		{
			*(result + pos) = '1';
		}
		else if(node->right == tmp)
		{
			*(result + pos) = '0';
		}
		++pos;
	}

	for(size_t i = 0; i < pos / 2; ++i)
	{
		char tmp = *(result + i); 
		*(result + i) = *(result + pos - i - 1);
		*(result + pos - i - 1) = tmp;
	}
}

void tr_free(struct pq_node *node)
{
	if(node != NULL)
	{
		tr_free(node->left);
		tr_free(node->right);
		free(node);
	}
}