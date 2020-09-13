#include "btree.h"
// Что дела(ет/л) этот метод:
// 1. Извлекает минимальные элементы и кладёт их в массив в порядке увеличения
// 2. Достраивает дерево, ввиде массива, складывая элементы и засосывая получившееся значение в конец
// 3. Переворачивает массив, чтобы дерево было корректным.
// Тут напрашивается очервидная оптимизация, но мы сейчас меняем архитектуру, так что нет.
// Задача данной функции, лишь дать нам память.
void init_tree(struct tree **tree, size_t size)
{
	(*tree) = malloc(sizeof(struct tree));
	(*tree)->array = calloc(size, sizeof(struct node));
	(*tree)->size = 0;
	(*tree)->capacity = size;
	/**
	(*tree)->array = calloc(size + size - 1, sizeof(struct node));	//????
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
	*/
}
