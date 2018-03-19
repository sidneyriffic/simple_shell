#include "shell.h"
#define DEBUGMODE
int checkpath(char *av[])
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
			pathlen = cmdcall(av);
			free(path);
			return (pathlen);
		}
		free(path);
		while (*pathvar == ':')
			pathvar++;
	}
	return (1);
}


int cmdcall(char *av[])
{
	char **environ;
	pid_t command;
	int status;

#ifdef DEBUGMODE
	printf("In cmdcall av[0]:%s\n", av[0]);
#endif
	if((environ = getallenv()) == NULL)
		return (-1);
	printf("Forking\n");
	command = fork();
	printf("command:%d\n", command);
	fflush(stdout);
	if (command == 0)
	{
#ifdef DEBUGMODE
		printf("Executing %s\n", av[0]);
#endif
		if (execve(av[0], av, environ) == -1)
		{
			perror("Could not execute command");
			exit(-1);
		}
#ifdef DEBUGMODE
		printf("Command done\n");
#endif
	}
	else
	{
		wait(&status);
	}
	printf("Status %d\n", status);
	free(environ);
	return (status);
}

int builtincall(char *av[])
{
	if (av[0] == NULL)
		return (0);
#ifdef DEBUGMODE
	printf("In builtincall %p\n%s\n", av[0], av[0]);
#endif
	if (!strcmp(av[0], "cd"))
		return (_cd(av));
	if (!strcmp(av[0], "exit"))
	{
		if (av[1] != NULL)
			exit(31337);
		else
			exit(0);
	}
	if (!strcmp(av[0], "getenv"))
		return (printf("%s\n", _getenv(av[1])));
	if (!strcmp(av[0], "setenv"))
		return (_setenv(av[1], av[2]));
	if (!strcmp(av[0], "alias"))
		return (aliascmd(av));
	if (av[0][0] != '/')
		return (checkpath(av));
	return (cmdcall(av));
}
