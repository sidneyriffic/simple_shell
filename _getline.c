#include "shell.h"
int _fgetc (FILE *stream)
{
	int c;
	int fd = (stream->_fileno);
	c = read(fd, &c, 1);
	return (c);
}
char *_fgets(char *s, int size, FILE *stream)
{
	char *ptr;
	int y;
	int x;

	x = 0;
	while (x < size)
	{
		if ((y = _fgetc(stream) == EOF)) //get 1 char
		{
			*ptr = '\0'; //if end of file make null byte @ location
			break;
		}
		if (y == '\n') //if newline send back to _getline to handle
			break;
		*ptr = y; //else *ptr set to char from fgetc
		ptr++; //increase ptr
		x++; //increase x
	}
	*ptr = 0; //set final ptr to null if goes through entire loop
	return (ptr);
}
       
int _getline(char **lineptr, size_t *n, FILE *stream)
{

	static char line[1024];
	char *c;
	int increase;
	int len;
	
	if (lineptr == NULL || n == NULL)
		return (1);

	_fgets(line, 1024, stream);

	c = _strchr(line, '\n'); //search for instance of newline
	if (c)
		*c = '\0'; //replace with null
	len = _strlen(line);

	if ((len + 1) >= 1024) //check for need to realloc
	{
		c = _realloc(*lineptr, 0, len + 1);
		if (c == NULL)
			return(-1);
		*lineptr = c;
		*n = 1024;
	}
	_strcpy(*lineptr,line);//copy line into lineptr
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
