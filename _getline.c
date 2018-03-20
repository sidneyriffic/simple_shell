#include "shell.h"
char *_fgets(char *s, int size, FILE *stream)
{
	char *ptr;
	int y;
	int x;

	x = 0;
	while (x < size)
	{
		if ((y = fgetc(stream) == EOF))
		{
			*ptr = '\0';
			break;
		}
		if (y == '\n')
			break;
		*ptr = y;
		ptr++;
		x++;
	}
	*ptr = 0;
	return (ptr);
}
       
int _getline(char **lineptr, size_t *n, FILE *stream)
{

	static char line[1024];
	char *c;
	unsigned int len;
	
	if (lineptr == NULL || n == NULL)
		return (1);

	fgets(line, 1024, stream);

	c = _strchr(line, '\n');
	if (c)
		*c = '\0';
	len = _strlen(line);

	if ((len + 1) < 1024)
	{
		c = realloc(*lineptr, 1024);
		if (c == NULL)
			return(-1);
		*lineptr = c;
		*n = 1024;
	}
	_strcpy(*lineptr,line);//strcpy
	return(len);
}

int main(int ac, char **av)
{
    char *buffer;
    FILE *file;
    int i;
    size_t bufsize = 0;
    ssize_t characters;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if(buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }   
    file = fopen(av[1], "r+");

    characters = _getline(&buffer, &bufsize, file);
    printf("%lu characters were read.\n",characters);
    printf("'%s'\n", buffer);

    characters = _getline(&buffer, &bufsize, file);
    printf("%lu characters were read.\n",characters);
    printf("'%s'\n", buffer);

    characters = _getline(&buffer, &bufsize, file);
    printf("%lu characters were read.\n",characters);
    printf("'%s'\n", buffer);

     characters = _getline(&buffer, &bufsize, file);
    printf("%lu characters were read.\n",characters);
    printf("'%s'\n", buffer);

    return(0);
}
