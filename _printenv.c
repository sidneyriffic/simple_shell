#include "shell.h"
extern char **environ;

int _printenv()
{
	int i;
	int j;

	i = 0;
	while (environ[i])
	{
		j = 0;
		while(environ[i][j] != 0)
		{
			_putchar(environ[i][j]);
			j++;
		}
		_putchar('\n');
		i++;
	}
	return (0);
}
