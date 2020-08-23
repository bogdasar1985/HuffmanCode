#include "priority_queue.h"
#include "btree.h"
#include <stdio.h>
int main(int argc, char* argv[])
{
	struct node *queue = NULL;
	FILE *fl = NULL;
	char ch = 0x0;
	struct node *res = NULL;

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
	//TODO: тут ошибка.
	while(queue != NULL)
	{
		struct node *tmp1 = get_min_symbol(&queue);
		struct node *tmp2 = get_min_symbol(&queue);
		res = merge(tmp1, tmp2);
		//Добавляем ноду без символа в очередь.
		q_add_node(res, &queue);
	}
	fclose(fl);
	return 0;
}
