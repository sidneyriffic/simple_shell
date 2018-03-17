#include "shell.h"

int parseargs(char *buf, char **environ)
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
		cmd[cc++] = strtok(NULL, cmdd);
#ifdef DEBUGMODE
		printf("Got cs %s", cmd[cc - 1]);
#endif
	}
	cc = 0;
	while (cmd[cc] != NULL)
	{
		ac = 0;
		av[ac++] = strtok(cmd[cc], wordd);
#ifdef DEBUGMODE
		printf("Got arg %s\n", av[ac - 1]);
#endif
		while (av[ac - 1] != NULL)
		{
			av[ac++] = strtok(NULL, wordd);
#ifdef DEBUGMODE
			printf("Got arg %s\n", av[ac -1]);
#endif
		}
		ac--;
		av[ac] = NULL;
#ifdef DEBUGMODE
		printf("Calling command/builtin\n");
#endif
		ret = builtincall(av, environ);
		cc++;
	}
	return (ret);
}
