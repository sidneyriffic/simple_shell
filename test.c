#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
/**
 *
 *
 */
size_t _getline(char **buf, size_t size, FILE *stream)
{
    size_t count = 0;
    char c;
    while ((c = (char)getc(stream)) != '\n' && count < size - 1) {
        buf[count++] = c;
    }
    buf[count] = '\0';
    return count;
}
int main()
{
    char *buffer;
    size_t bufsize = 32;
    size_t characters;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if( buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }

    printf("Type something: ");
    characters = _getline(&buffer,&bufsize,stdin);
    printf("%lu characters were read.\n",characters);
    printf("You typed: '%s'\n",buffer);

    return(0);
}
