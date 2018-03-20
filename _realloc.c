#include "shell.h"
/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: void pointer
 * @old_size: unsigned int
 * @new_size: unsigned int
 *
 * Return: pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *s;

	if (new_size > old_size)
	{
		s = malloc(new_size);
		free(ptr);
		return (s);
	}
	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
	{
		s = malloc(new_size);
		return (s);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}
