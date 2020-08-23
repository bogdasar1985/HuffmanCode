#include "priority_queue.h"
//TODO: проверки на NULL
//TODO: протестировать
struct node *search_node(char symbol, struct node *list)
{
	struct node *tmp = list;
	while(tmp != NULL)
	{
		if(tmp->symbol == symbol)
		{
			return tmp;
		}
		tmp = tmp->next;
	}
	return tmp;	//Если не нашёл, вернуть NULL.
}

int add_symbol(char symbol, struct node **list)
{
	struct node *res = NULL;

	//Если данный символ имеется, то прибавляем 1.
	if((res = search_node(symbol, *list)) != NULL)
	{
		res->counter++;
		return 1;
	}
	
	//Если нет, то добавляем в очередь.
	res = malloc(sizeof(struct node));
	res->symbol = symbol;
	res->counter = 1;
	res->next = *list;
	res->left = NULL;
	res->right = NULL;
	*list = res;
	return 0;
}

struct node *get_min_symbol(struct node **list)
{
	struct node *tmp = *list;
	unsigned long long min_counter = tmp->counter;
	struct node *min_node = tmp;

	while(tmp != NULL)
	{
		if(tmp->counter < min_counter)
		{
			min_counter = tmp->counter;
			min_node = tmp;
		}
		tmp = tmp->next;
	}	
	//Мы нашли элемент(min_node). Тут произвести его извлечение из очереди.
	tmp = *list;

	while(tmp != NULL)
	{
		if(tmp == min_node)
		{
			*list = min_node->next;
			min_node->next = NULL;
			return min_node;
		}
		else if(tmp->next == min_node)
		{
			tmp->next = min_node->next;
			min_node->next = NULL;
			return min_node;
		}
		tmp = tmp->next;
	}

	return min_node;
}

int q_add_node(struct node *node, struct node **queue)
{
	if(node == NULL || *queue == NULL)
	{
		return -1;
	}
	node->next = *queue;
	*queue = node;
	return 0;
}
