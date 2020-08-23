//TODO: Разобраться с русскими символами.
//TODO: О реализации бинарного древа:
//	1. Каждый элемент очереди, уже по сути, является деревом с одной нодой.
//	2. Далее, нам надо лишь производить слияние деревьев, пока все не срастутся в одно.
#include <stdio.h>
#include "priority_queue.h"
int main(int argc, char *argv[])
{
	struct node *queue = NULL;
	struct node *tmp = NULL;
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

	while((fread(&ch, 1, 1, fl)) != 0)
	{
		add_symbol(ch, &queue);
	}

	//Высвобождение ресурсов.
	while(queue != NULL)
	{
		tmp = get_min_symbol(&queue);
		printf("%c : %lld\n", tmp->symbol, tmp->counter);
		free(tmp);
	}
	fclose(fl);
	return 0;
}
