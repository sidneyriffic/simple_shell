#include "shell.h"
int history (char *cmd)
{
	int count_max = 1000;
	int i;
	static int count = 0;
	char *history[1000];

	if (count < count_max)
	{
		history[count] = _strdup(*cmd);
		count++;
	}
	else
	{
		free(history[0]);
		i = 0;
		while (i < count_max)
		{
			history[i] = history[i + 1];
			i++;
		}
		history[i] = _strdup(*cmd);
	}
	count = i;
	return (0);
}
