//TODO: Разобраться с русскими символами.
//TODO: О реализации бинарного древа:
//	1. Каждый элемент очереди, уже по сути, является деревом с одной нодой.
//	2. Далее, нам надо лишь производить слияние деревьев, пока все не срастутся в одно.
#include <stdio.h>
#include "heap.h"
int main(int argc, char *argv[])
{
	struct node tmp;
	struct heap *queue = NULL;
	FILE *fl = NULL;
	char ch = 0x0;

	if(argc < 2)
	{
		fprintf(stderr, "Too few arguments!\n");
		return -1;
	}

	if((fl = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "Wrong file name!\n");
		return -2;
	}
	
	init_heap(&queue);

	while((fread(&ch, 1, 1, fl)) != 0)
	{
		insert(&queue, ch);
	}

	//Высвобождение ресурсов.
	while(queue->size != 0)
	{
		tmp = extract_min(&queue);
		printf("%c : %lld\n", tmp.symbol, tmp.frequency);
	}
	free(queue->array);
	free(queue);
	fclose(fl);
	return 0;
}
