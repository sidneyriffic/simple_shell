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
	return (s1[i] - s2[i]);
}
/**
 * _strlen - string length
 * @str: string
 * Return: length
 */
size_t _strlen(char *str)
{
	size_t len = 0;

	while (*str++)
		len++;

	return (len);
}
/**
 * _strcpy - string copy
 * @dest: dest string
 * @src: source string
 * Return: string
 */
char *_strcpy(char *dest, char *src)
{
	char *ptr = dest;

	while (*src)
		*ptr++ = *src++;
	*ptr = *src;

	return (dest);
}
/**
 * _strdup - string duplication
 * @str: string
 * Return: string
 */
char *_strdup(char *str)
{
	char *new;

	if (str == NULL)
		return (NULL);
	new = malloc(sizeof(char) * (_strlen(str) + 1));
	if (new == NULL)
		return (NULL);
	_strcpy(new, str);
	return (new);
}
/**
 * _strcat - string concnat
 * @dest: destination
 * @src: source
 * Return: concated string
 */
char *_strcat(char *dest, char *src)
{
	char *ptr = dest;

	while (*ptr)
		ptr++;
	while (*src)
		*ptr++ = *src++;
	*ptr = 0;
	return (dest);
}
