#include "shell.h"
int _getline(char **lineptr, int fd)
{
	int size = 1024;
	int old_size;
	char *line;
	int r = 0;
	static char buffer[1024];
	static int begin;
	static int end;
	int c = 0;
	int retval;

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

	while(1)
	{
		if (begin == end)
		{
			/*printf("reading\n");*/
			r = read(0, buffer, 1024);
			if (r == 0)
				return(c);
			end = r;
			begin = 0;
		}

		for (c; buffer[begin] && c < size; begin++)
		{
			if (buffer[begin] == EOF)
			{
			/*printf("inside r == 0 loop:%d\n" , i);*/
			//	free(buffer);
				(*lineptr)[c] = EOF;
				return(c);
			}
		/*printf("beginning for\n");//debug check*/
			else if(buffer[begin] == '\n')
			{
				(*lineptr)[c] = '\n';
				(*lineptr)[c + 1] = '\0';
				begin++;
				//free (buffer);
				/*printf("%d\n", c);*/
				return(c + 1);
			}
			else
				(*lineptr)[c] = buffer[begin];
			c++;
		}
		/*printf("exiting for\n");//debug check*/
		/*printf("i: %d\n", i);//debug check*/
		if (c >= 1024)
		{
			old_size = size;
			size = size + 1024;
			*lineptr = _realloc(*lineptr, old_size ,size);
			if (line == NULL)
			{
				//free(buffer);
				return(-1);
			}
			/*printf("realloc line: %d, c : %d r: %d\n", begin, c, r);*/
		}
		/*printf("j: %d, i:%d, r:%d\n", j, i ,r);*/
	}
}
