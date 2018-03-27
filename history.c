#include "shell.h"
	static int count = 0;
	static char *buffer[4096];
void history(char *cmd)
{
	int i;
	if (count < 4096)
	{
		buffer[count] = _strdup(cmd);
		count++;
	}
	else
	{
		free(buffer[0]);
		i = 1;
		while (i < 4096)
		{
			buffer[i - 1] = buffer[i];
			i++;
		}
		buffer[4096 - 1] = _strdup(cmd);
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
int exit_hist()
{
	int fd;
	int i, len, w;
	char *s;

	fd = open(.simple_shell_history, O_CREAT | O_RDWR | O_TRUNC);
	if (fd == -1)
		return (-1);

	i = 0;
	while (buffer[i])
	{
		s = buffer[i];
		len = _strlen(s);
		w = write(fd, s, len);
		if (w == -1)
			return (-1);
		i++;
	}

	while (buffer[i])
	{
		free(buffer[i]);
		i--;
	}
	free(buffer);

	close(fd);

	return(1);
}
