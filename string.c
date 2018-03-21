#include "shell.h"
/**
 * _strcmp - compares two strings
 * @s1: char pointer
 * @s2: char pointer
 *
 * _strcmp: compares two strings at the same spot on each string
 * Returns positive, negative, or 0 if theyre the same
 * Return: int i
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

size_t _strlen(char *str)
{
	size_t len = 0;

	while (*str++)
		len++;

	return (len);
}

char *_strcpy(char *dest, char *src)
{
	while(*src)
		*dest++ = *src++;
	*dest = *src;

	return (dest);
}

char *_strdup(char *str)
{
	char *new;

	if (str == NULL)
		return (NULL);
	new = malloc(sizeof(char) * _strlen(str));
	if (new == NULL)
		return (NULL);
	_strcpy(new, str);
	return (new);
}
