#include "shell.h"

int cmdcall(char *av[])
{
	pid_t command;
	int status;

	printf("av[0] %s av[1] %s\n", av[0], av[1]);
	command = fork();
	if (command == 0)
	{
		printf("Child executing command %s\n", av[0]);
		if (execve(av[0], av, NULL) == -1)
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

int builtincall(char *av[])
{
	if (av[0][0] == 'e' && av[0][1] == 'x' && av[0][2] == 'i'
	    && av[0][3] == 't' && av[0][4] == 0)
	{
		if (av[1] != NULL)
			exit(31337);
		else
			exit(0);
	}
	return (cmdcall(av));
}
