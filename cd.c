#include "shell.h"
/**
 *_cd - change directory builtin
 * @av: argument
 * Return: int ret
 */
int _cd(char *av[])
{
	char *buf = NULL;
	int ret;

	printf("in cd\n");
	buf = getcwd(buf, 0);
	if (buf == NULL)
		return (-1);
	if (av[1] == NULL || av[1][0] == 0 ||
	    (av[1][0] == '~' && av[1][1] == 0))
		av[1] = _getenv("HOME");
	if (av[1][0] == '-' && av[1][1] == 0)
		av[1] = _getenv("OLDPWD");
	ret = chdir(av[1]);
	if (ret == 0)
	{
		_setenv("OLDPWD", buf);
		free(buf);
		_setenv("PWD", av[1]);
		return (0);
	}
	free(buf);
	return (ret);
}
