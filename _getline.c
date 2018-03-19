#include "shell.h"
/**
 *
 *
 */
int _getline(char **s, size_t n)
{
	int i;

	i = read(STDIN_FILENO, *s, 1024);
	if (i == -1)
	{
		perror("Error");
		return (-1);
	}
	return (i);
}


int main()
{
    char *buffer;
    size_t bufsize = 1024;
    size_t characters;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if( buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }

    characters = _getline(&buffer, bufsize);
    printf("%lu characters were read.\n",characters);
    printf("'%s'\n", buffer);

    return(0);
}
