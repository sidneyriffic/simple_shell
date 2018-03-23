#include "shell.h"
char *_getline()
{
	int size = 1024;
	int old_size = 0;
	char *buffer;
	char *line;
	int r = 0;
	int j = 0;
	int i;

	buffer = malloc(sizeof(char) * size);
	if (buffer == NULL)
		return (NULL);
	line = malloc(sizeof(char) * size);
	if (line == NULL)
		return (NULL);

	do {
		r = read(0, buffer, 1024);
		/*printf("beginning for\n");//debug check*/
		for (i = 0;i <= r; i++)
		{
			if(buffer[i] == EOF)
			{
				line[i + j] = buffer[i];
				free(buffer);
				return(line);
			}
			else if (buffer[i] == '\n')
			{
				line[i + j] = '\0';
				free(buffer);
				return(line);
			}
			else
				line[i + j] = buffer[i];
		}
		/*printf("exiting for\n");//debug check*/
		i--;
		/*printf("i: %d\n", i);//debug check*/
		if (i >= 1024)
		{
			old_size = size;
			size = size + 1024;
			line = _realloc(line, old_size ,size);
			if (line == NULL)
			{
				return(NULL);
			}
			/*printf("realloc line: %d\n", size);*/
		}
		j = j + 1024;
		/*printf("j: %d\n, i:%d, r:%d", j, i ,r);*/
	}while(i == r);
}
