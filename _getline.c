#include "shell.h"
char *_getline(int fd)
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

	line = malloc(sizeof(char) * size);
	if (line == NULL)
	{
		return (NULL);
	}

	while(1)
	{
		if (begin == end)
		{
			/*printf("reading\n");*/
			r = read(0, buffer, 1024);
			if (r == 0)
				return(line);
			end = r;
			begin = 0;
		}

		for (c; buffer[begin] && c < size; begin++)
		{
			if (buffer[begin] == EOF)
			{
			/*printf("inside r == 0 loop:%d\n" , i);*/
			//	free(buffer);
				line[c] = EOF;
				return(line);
			}
		/*printf("beginning for\n");//debug check*/
			else if(buffer[begin] == '\n')
			{
				line[c] = '\0';
				begin++;
				//free (buffer);
				return(line);
			}
			else
				line[c] = buffer[begin];
			c++;
		}
		/*printf("exiting for\n");//debug check*/
		/*printf("i: %d\n", i);//debug check*/
		if (c >= 1024)
		{
			old_size = size;
			size = size + 1024;
			line = _realloc(line, old_size ,size);
			if (line == NULL)
			{
				//free(buffer);
				return(NULL);
			}
			/*printf("realloc line: %d, c : %d r: %d\n", begin, c, r);*/
		}
		/*printf("j: %d, i:%d, r:%d\n", j, i ,r);*/
	}
}
