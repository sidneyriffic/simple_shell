#include "shell.h"

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
			perror("Could not execute command errno:");
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
	return (cmdcall(av, environ));
}
