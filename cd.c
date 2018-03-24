#include "shell.h"

int _cd(char *av[])
{
	char *oldpwd = NULL, *newpath;
	int ret;

	oldpwd = getcwd(oldpwd, 0);
	if (oldpwd == NULL)
		return (-1);
	if (av[1] == NULL || av[1][0] == 0)
		av[1] = _getenv("HOME");
	else if (av[1][0] == '-' && av[1][1] == 0)
		av[1] = _getenv("OLDPWD");
	else if (av[1][0] != '/')
	{
		newpath = malloc(_strlen(oldpwd) + _strlen(av[1]) + 2);
		_strcat(newpath, oldpwd);
		_strcat(newpath, "/");
		_strcat(newpath, av[1]);
	}
	ret = chdir(av[1]);
	if (ret == 0)
	{
		_setenv("OLDPWD", oldpwd);
		free(oldpwd);
		_setenv("PWD", av[1]);
		return (0);
	}
	free(oldpwd);
	return (ret);
}
