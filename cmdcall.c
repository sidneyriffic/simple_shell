#include "shell.h"

/**
 * checkpath - checks the path
 * @av: arguments
 * Return: 1
 */
int checkpath(char *av[])
{
	char *path, *pathptr, *pathvar, *ptr, *pathenv;
	int pathlen, cmdlen;

#ifdef DEBUGMODE
	printf("In checkpath\n");
#endif
	for (ptr = av[0], cmdlen = 0; *ptr != 0; ptr++)
		cmdlen++;
	pathvar = _getenv("PATH");
	pathenv = pathvar;
	while (*pathvar != 0)
	{
		for (pathlen = 0, ptr = pathvar; *ptr != 0 && *ptr != ':'; ptr++)
			pathlen++;
		path = malloc(sizeof(char) * (cmdlen + pathlen + 2));
		if (path == NULL)
		{
			free(pathenv);
			return (-1);
		}
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
#ifdef DEBUGMODE
			printf("Found path:%s\n", path);
#endif
			pathlen = cmdcall(av, path);
			free(path);
			free(pathenv);
			return (pathlen);
		}
		free(path);
		while (*pathvar == ':')
			pathvar++;
	}
	printerr();
	free(pathenv);
	return (1);
}
/**
 * cmdcall - calls commands
 * @av: arguments
 * Return: retval
 */
int cmdcall(char *av[], char *cmd)
{
	pid_t command;
	int status;

#ifdef DEBUGMODE
	printf("In cmdcall av[0]:%s\n", av[0]);
#endif
	if ((environ = getallenv()) == NULL)
		return (-1);
#ifdef DEBUGMODE
	printf("Forking\n");
#endif
	command = fork();
#ifdef DEBUGMODE
	printf("command:%d\n", command);
	fflush(stdout);
#endif
	if (command == 0)
	{
#ifdef DEBUGMODE
		printf("Executing %s\n", av[0]);
#endif
		if (execve(cmd, av, *(getenviron())) == -1)
		{
			printerr();
			exit(1);
		}
#ifdef DEBUGMODE
		printf("Command done\n");
#endif
	}
	else
	{
		wait(&status);
	}
#ifdef DEBUGMODE
	printf("Status %d\n", status);
#endif
	free(environ);
	return (status);
}
/**
 * builtincall - calls builtin commands
 * @av: arguments
 * Return: retval
 */
int builtincall(char *av[])
{
	int retval = 0;
	char *retstr;

	if (av[0] == NULL)
		return (0);
#ifdef DEBUGMODE
	printf("In builtincall %p\n%s\n", av[0], av[0]);
	printf("av[1]:%s\n", av[1]);
#endif
	if (!_strcmp(av[0], "exit"))
	{
		if (av[1] != NULL)
			exit(atoi(av[1]) % 256);
		else
			exit(0);
	}
	if (!_strcmp(av[0], "cd"))
		retval = _cd(av);
/*	else if (!_strcmp(av[0], "getenv"))
	retval = !printf("%s\n", _getenv(av[1]));*/
	else if (!_strcmp(av[0], "history"))
		print_hist();
	else if (!_strcmp(av[0], "env"))
		retval = _printenv(av[1]);
	else if (!_strcmp(av[0], "setenv"))
		retval = _setenv(av[1], av[2]);
	else if (!_strcmp(av[0], "unsetenv"))
		retval = _unsetenv(av[1]);
	else if (!_strcmp(av[0], "alias"))
		retval = aliascmd(av);
	else if (!_strcmp(av[0], "unset"))
		retval = unsetsvar(av[1]);
	else if (!_strcmp(av[0], "unalias"))
		retval = unsetalias(av[1]);
	else if (av[0][0] != '/')
		retval = checkpath(av);
	else
		retval = cmdcall(av, av[0]);
#ifdef DEBUGMODE
	printf("After call back in builtin retval:%d\n", retval);
#endif
	if (retval % 256 == 0 && retval != 0)
		retval = 1;
	retstr = itos(retval % 128);
#ifdef DEBUGMODE
	printf("Status string:%s\n", retstr);
#endif
	setsvar("?", retstr);
	free(retstr);
	return (retval);
}
