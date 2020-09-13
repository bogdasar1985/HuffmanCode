#ifndef BTREE
#define BTREE
#include <stdlib.h>
#include <string.h>
#include "node.h"
// Это определение структуры. Хули оно тут делает?
// Нельзя так блять! Нарушение инкапсуляции.
// Устранив это, мы сможем усранить зависимость дерева от кучи.
// 0. Убрать "heap.h"
// 1. Изменить метод init_tree, сделав его независимым от "heap.h", уменьшить функционал, 
//    тем самым, уменьшить зону ответственности.
// 1.1 Мы будем инициализироваться, исходя из аргумента size, который возьмём у queue.
// 1.2 А заполнять дерево из очереди, будем в файле "huffman.h"
// 2. get_code() и char_swap() - это зона ответственности "huffman.h"
struct tree
{
    struct node *array;
    size_t capacity;
    size_t size;
};

void init_tree(struct tree **tree, size_t size);

//void char_swap(char *first, char *second);

//void get_code(struct tree *queue, size_t index, char *result);
#endif