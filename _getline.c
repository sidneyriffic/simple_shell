#include "shell.h"
/**
 * _getline - gets a line from fd or std input
 * @lineptr: buffer to fill line with
 * @fd: file descriptor
 * Return: num of characters
 */
int _getline(char **lineptr, __attribute__((unused)) int fd)
{
	int size = 1024;
	int old_size;
	int r = 0;
	static char buffer[1024];
	static int begin;
	static int end;
	int c = 0;

	if (lineptr == NULL)
	{
		return (0);
	}
	if (*lineptr == NULL)
	{
		*lineptr = malloc(sizeof(char) * size);
		if (*lineptr == NULL)
			return (-1);
	}

	while (1)
	{
		if (begin == end)
		{
			/*printf("reading\n");*/
			r = read(0, buffer, 1024);
			if (r == 0)
				return (c);
			end = r;
			begin = 0;
			/*printf("r : %d\n", r);*/
		}

		for (; buffer[begin] && c < size; begin++)
		{
			if (begin == 1024)
			{
			/*free(buffer);*/
				/*(*lineptr)[c] = EOF;*/
				/*return (c);*/
				break;
			}
		/*printf("beginning for\n");//debug check*/
			if (buffer[begin] == '\n')
			{
				(*lineptr)[c] = '\n';
				begin++;
				c++;
				(*lineptr)[c] = '\0';
				return (c);
			}
			else
			{
				(*lineptr)[c] = buffer[begin];
			}
			c++;
		}
		if (c + begin >= 1024)
		{
			old_size = size;
			size = size + 1024;
			*lineptr = _realloc(*lineptr, old_size, size);
			if (*lineptr == NULL)
			{
				return (-1);
			}
		}
		else
			return (c);
		/*printf("j: %d, i:%d, r:%d\n", j, i ,r);*/
	}
}
