#include "shell.h"

int checkpath(char *av[], char **environ)
{
	char *path, *pathptr, *pathvar, *ptr;
	int pathlen, cmdlen;

	for (ptr = av[0], cmdlen = 0; *ptr != 0; ptr++)
		cmdlen++;
	pathvar = _getenv("PATH");
	while (*pathvar != 0)
	{
		for (pathlen = 0, ptr = pathvar; *ptr != 0 && *ptr != ':'; ptr++)
			pathlen++;
		path = malloc(sizeof(char) * (cmdlen + pathlen + 2));
		if (path == NULL)
			return (-1);
		pathptr = path;
		while (*pathvar != ':' && *pathvar != 0)
			*pathptr++ = *pathvar++;
		*pathptr++ = '/';
		ptr = av[0];
		while (*ptr != 0)
			*pathptr++ = *ptr++;
		*pathptr = 0;
		if (!access(path, F_OK))
		{
			av[0] = path;
			pathlen = cmdcall(av, environ);
			free(path);
			return (pathlen);
		}
		free(path);
		while (*pathvar == ':')
			pathvar++;
	}
	return (1);
}


int cmdcall(char *av[], char **environ)
{
	pid_t command;
	int status;

	printf("av[0] %s av[1] %s\n", av[0], av[1]);
	command = fork();
	if (command == 0)
	{
		printf("Child executing command %s\n", av[0]);
		if (execve(av[0], av, environ) == -1)
		{
			perror("Could not execute command");
			exit(-1);
		}
		printf("Child done\n");
	}
	else
	{
		printf("Parent waiting\n");
		wait(&status);
		printf("Parent done\n");
	}
	printf("You shouldn't see this until command is done\n");
	return (status);
}

int builtincall(char *av[], char **environ)
{
	if (!strcmp(av[0], "exit"))
	{
		if (av[1] != NULL)
			exit(31337);
		else
			exit(0);
	}
	else if (!strcmp(av[0], "getenv"))
	{
		return (printf("%s\n", _getenv(av[1])));
	}
	if (av[0][0] != '/')
		return (checkpath(av, environ));
	return (cmdcall(av, environ));
}
