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
			return (s1[i] - s2[i]);
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

	return (dest);
}

char *malcat(char *dest, char *src)
{
	int len_dest;
	int len_src;
	int i, j;
	char *s;

	printf("In malcat\n");
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
