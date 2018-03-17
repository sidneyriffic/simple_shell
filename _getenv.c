#include "shell.h"
extern char **environ;
/**
 * _strcat - concatenates two strings
 * @dest: char pointer
 * @src: char pointer
 *
 * _strcat: concatenates two strings
 *
 * Return: char pointer
 */
char *malcat(char *dest, char *src)
{
	int len_dest;
	int len_src;
	int i;

	len_dest = 0;
	while (dest[len_dest] != '\0')
	{
		len_dest++;
	}
	i = 0;
	len_src = 0;
	while (src[len_src] != '\0')
	{
		len_src++;
	}
	i = len_src + len_dest;
	i++;
	s = malloc(sizeof(char) * i);
	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (dest[i] != 0)
	{
		s[j++] = dest[i++];
	}
	i = 0;
	while (src[i] != 0)
	{
		s[j++] = src[i++];
	}
	s[j] = 0;

	return (s);
}
char *_getenv(const char *name)
{
	char *s;
	int i;

	i = 0;
	while (environ[i] != 0)
	{
		s = environ[i];
		j = 0;
		while (s[j] == name[j])
		{
			if (name[j] == 0 && s[j] == '=')
				return (strcat(environ[i], name));
			j++;
		}
		i++;
	}
	return(NULL);
}
