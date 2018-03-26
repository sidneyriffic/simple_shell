#include "shell.h"

int _cd(char *av[])
{
	char *oldpwd = NULL, *newpath, *pathbit, *newptr;
	int ret;

	oldpwd = getcwd(oldpwd, 0);
	if (oldpwd == NULL)
		return (1);
	if (av[1] == NULL || av[1][0] == 0)
	{
		newpath = _getenv("HOME");
	}
	else if (av[1][0] == '-' && av[1][1] == 0)
	{
		/*check getenv malloc error here and above*/
		newpath = _getenv("OLDPWD");
	}
	else
	{
#ifdef DEBUGCD
		printf("Making new path %s:%c\n", av[1], av[1][0]);
#endif
		newpath = malloc(sizeof(char)* (_strlen(oldpwd) + _strlen(av[1]) + 2));
		if (newpath == NULL)
			return (-1);
		newptr = newpath;
		pathbit = oldpwd;
		if (av[1][0] != '/' && pathbit[1] != 0)
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
		if (newptr != newpath && newptr != newpath + 1)
			newptr--;
		*newptr = 0;
#ifdef DEBUGCD
		printf("New path:%s\n", newpath);
#endif
	}
	ret = chdir(newpath);
	if (ret == 0)
	{
		_setenv("OLDPWD", oldpwd);
		free(oldpwd);
		_setenv("PWD", newpath);
		return (0);
	}
	free(oldpwd);
	free(newpath);
	return (ret);
}
