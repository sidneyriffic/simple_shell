#include "shell.h"
	static int count = 0;
	static char *buffer[4096];
void history(char *cmd)
{
	int i;
	if (count < 1024)
	{
		buffer[count] = _strdup(cmd);
		count++;
	}
	else
	{
		free(buffer[0]);
		i = 1;
		while (i < 1024)
		{
			buffer[i - 1] = buffer[i];
			i++;
		}
		buffer[1024 - 1] = _strdup(cmd);
	}
}
void print_hist()
{
	int i, j;
	int c;
	int len;
	char *s;
	char *num;

	i = 0;
	while (buffer[i])
	{
		s = buffer[i];
		len = _strlen(s);
		num = itos(i);
		j = 0;
		while (num[j] != '\0')
		{
			_putchar(num[j]);
			j++;
		}
		_putchar(' ');
		j = 0;
		while (s[j] != '\0')
		{
			_putchar(s[j]);
			j++;
		}
		i++;
	}
}
