#include "shell.h"

/*int freeargs(char *av[])
{
	int i = 0;
	printf("%p\n", NULL);
	while (av[i] != NULL)
	{
		printf("free arg %p\n", av[i]);
		free(av[i++]);
		printf("freed! next arg %p %p\n", av[i]);
	}
	printf("Out of free while\n");
	return (0);
	}*/

int parseargs(char *buf)
{
	char *av[1024];
	int ac = 0;
	char *delim = " ";

	av[ac++] = strtok(buf, delim);
	printf("Got arg %s\n", av[ac - 1]);
	while (av[ac - 1] != NULL)
	{
		printf("Parsing arg %d\n", ac);
		av[ac] = strtok(NULL, delim);
		printf("Got arg %s\n", av[ac]);
		ac++;
	}
	printf("Calling command/builtin\n");
	if (ac[0] == NULL)
		return (0);
	ac = builtincall(av);
	return (ac);
}
