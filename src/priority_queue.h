//Нам нужно приоритетное исключение, то есть, выбор приоритета будет происходить при его исключении.
//Очередь будет реализована на основе списка.
//TODO: реализовать на основе бинарной кучи.
#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE
#include <stdlib.h>
#include "node.h"
//Поиск символа в очереди и возвращения указателя на ноду с ним.
struct node *search_node(char symbol, struct node *list);

//Добавляем символ в очередь.
int add_symbol(char symbol, struct node **list);

//Добавляет ноду по указателю.
int q_add_node(struct node *node, struct node **queue);

//Ищет минимальную ноду и возвращает её.
struct node *get_min_symbol(struct node **list);
#endif
