#include "shell.h"

int _cd(char *av[])
{
	char *oldpwd = NULL, *newpath, *pathbit, *newptr;
	int ret;

	oldpwd = getcwd(oldpwd, 0);
	if (oldpwd == NULL)
		return (1);
	if (av[1] == NULL || av[1][0] == 0)
		av[1] = _getenv("HOME");
	else if (av[1][0] == '-' && av[1][1] == 0)
		av[1] = _getenv("OLDPWD");
	else
	{
		newpath = malloc(sizeof(char)* (_strlen(oldpwd) + _strlen(av[1]) + 1));
		if (newpath == NULL)
			return (-1);
		newptr = newpath;
		pathbit = oldpwd;
		if (av[1][0] != '/')
			while (*pathbit)
				*newptr++ = *pathbit++;
		*newptr++ = '/';
		pathbit = strtok(av[1], "/");
#ifdef DEBUGCD
		printf("starting newpath:%s:Pathbit got:%s\n", newpath, pathbit);
		printf("newpath/ptr diff:%p\n", newptr - newpath);
#endif
		while (pathbit != NULL)
		{
			if (pathbit[0] == '.' && pathbit[1] == '.'
			    && pathbit[2] == 0)
			{
#ifdef DEBUGCD
				printf("going back a directory%s:%s\n", newpath, newpath);
#endif
				newptr--;
				if (newptr != newpath)
					newptr --;
				while (*newptr != '/')
					newptr--;
				*newptr++ = '/';
			}
			else if (!(pathbit[0] == '.' && pathbit[1] == 0))
			{
				while (*pathbit)
					*newptr++ = *pathbit++;
				*newptr++ = '/';
			}
			pathbit = strtok(NULL, "/");
#ifdef DEBUGCD
			printf("Got pathbit:%s\n", pathbit);
#endif
		}
		*newptr = 0;
		newptr--;
		if (newptr != newpath)
			*newptr = 0;
#ifdef DEBUGCD
		printf("New path:%s\n", newpath);
#endif
		free(av[1]);
		av[1] = newpath;
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
