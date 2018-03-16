#include "shell.h"

int parseargs(char *buf)
{
	char *av[1024], *cmd[1024], *ptr;
	int ac, cc, ret = 0;
	char *wordd = " ", *cmdd = ";";

	if (buf[0] == 0)
		return (0);
	for (ptr = buf; *ptr != 0; ptr++)
		if (*ptr == '#' || *ptr == '\n')
		{
			*ptr = 0;
			break;
		}

	cc = 0;
	cmd[cc++] = strtok(buf, cmdd);
	while(cmd[cc - 1] != NULL)
	{
		printf("parsing command string %d\n", cc);
		cmd[cc++] = strtok(NULL, cmdd);
		printf("Got arg %s", cmd[cc - 1]);
	}
	cc = 0;
	while (cmd[cc] != NULL)
	{
		ac = 0;
		av[ac++] = strtok(cmd[cc], wordd);
		printf("Got arg %s\n", av[ac - 1]);
		while (av[ac - 1] != NULL)
		{
			printf("Parsing arg %d\n", ac);
			av[ac++] = strtok(NULL, wordd);
			printf("Got arg %s\n", av[ac -1]);
		}
		ac--;
		av[ac] = NULL;
		printf("Calling command/builtin\n");
		ret = builtincall(av);
		cc++;
	}
	return (ret);
}
