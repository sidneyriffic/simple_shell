#include "shell.h"
int _getc()
{
	static char buffer[1024];
	static int begin;
	static int end;
	int i = 0;
	int retval;


	if (begin == end)
	{
		i = read(0, buffer, 1024);
		if (i == 0)
			return(-1);
		end = i;
		begin = 0;
	}
	if (i >= 0)
	{
		retval = buffer[begin];
		begin++;
		return(retval);
		//begin++;
		//printf("%c: retval\n", retval);
		//return(retval);
	}
	return(-1);
}
char *_getline(char *file)
{
	int size = 256;
	int old_size;
	int fd;
	char *line;
	int r = 0;
	int i = 0;

	line = malloc(sizeof(char) * size);
	if (line == NULL)
	{
		return (NULL);
	}
	fd = open(file, O_RDWR);
	//if (fd == -1)
	//return (0);
	while(1)
	{
		r = _getc();
		//r = read(0, buffer, 1024);
		//printf("r: %d\n", r);
		if (r == -1)
		{
			/*printf("inside r == 0 loop:%d\n" , i);*/
			//	free(buffer);
			line[i] = '\0';
			return(line);
		}
		/*printf("beginning for\n");//debug check*/
		else if(r == '\n')
		{
			line[i] = '\0';
			//free (buffer);
			return(line);
		}
		else
			line[i] = r;
		i++;
		/*printf("exiting for\n");//debug check*/
		/*printf("i: %d\n", i);//debug check*/
		if (i >= 256)
		{
			old_size = size;
			size = size + 256;
			line = _realloc(line, old_size ,size);
			if (line == NULL)
			{
				//free(buffer);
				return(NULL);
			}
			/*printf("realloc line: %d, i : %d r: %d\n", size, i, r);*/
		}
		/*printf("j: %d, i:%d, r:%d\n", j, i ,r);*/
	}
}
