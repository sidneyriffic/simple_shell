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
	int old_size = 0;
	int r = 1;
	int sum = 0;
	static char buffer[1025];
	static int begin;
	static int end;
	int c = 0;

	if (lineptr == NULL)
	{
		return (0);
	}
	if (*lineptr == NULL)
	{
		*lineptr = malloc(sizeof(char) * size + 1);
		if (*lineptr == NULL)
			return (-1);
	}

	while (1)
	{
		if (begin == end)
		{
			while (sum < 1024 && r != 0)
			{
				/*printf("reading\n");*/
				r = read(0, buffer + sum, 1024);
				begin = 0;
				sum += r;
				end = sum;
				/*printf("r : %d\n", r);*/
				for (c = 0; r != 0 && c < end; c++)
					if (buffer[c] == '\n')
						r = 0;
			}
			if (sum == 0)
			{
				buffer[0] = 0;
				return(sum);
			}
			buffer[sum] = 0;
		}
		for (c = 0; buffer[begin] && c < size; begin++)
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
		{
			(*lineptr)[old_size + begin] = 0;
			return (c);
		}
		/*printf("j: %d, i:%d, r:%d\n", j, i ,r);*/
	}
}
