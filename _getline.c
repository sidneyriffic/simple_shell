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

	while (size > 0)
	{
		if ((y = _fgetc(stream) == EOF)) //get 1 char
		{
			break;
		}
		*ptr++ = y;
		if (y == '\n') //if newline send back to _getline to handle
			break;
		size--;
	}
	*ptr = 0;
	if (y == EOF)
		return (0);
	return(ptr);
}
int _getline(char **lineptr, size_t *n, FILE *stream)
{

	static char line[1024];
	char *c;
	int increase;
	int len;

	if (lineptr == NULL || n == NULL)
		return (1);

	fgets(line, 1024, stream);

	c = _strchr(line, '\n'); //search for instance of newline
	if (c)
		*c = '\0'; //replace with null
	len = _strlen(line);

	if ((len + 1) <= 1024) //check for need to realloc
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
