#include "shell.h"
#include "alias.h"

AliasData *alist;

char *get_alias(char *name)
{
	AliasData *ptr = alist;

	if (ptr == NULL)
		return (NULL);
	while (ptr -> name != name)
		ptr = ptr -> next;
	if (ptr == NULL)
		return (NULL);
	return (ptr -> val);
}

int set_alias(char *name, char *val)
{
	AliasData *ptr = alist, *new;

	if (alist == NULL)
	{
		new = malloc(sizeof(AliasData));
		if (new == NULL)
			return (-1);
		new -> name = name;
		new -> val = val;
		alist = new;
		return (0);
	}	
	while (ptr -> name != name && ptr -> next != NULL)
		ptr = ptr -> next;
	if (ptr -> name == name)
	{
		free(ptr -> val);
		ptr -> val = val;
	}
	else
	{
		new = malloc(sizeof(AliasData));
		if (new == NULL)
			return (-1);
		new -> name = name;
		new -> val = val;
		ptr -> next = new;
	}
	return (0);
}

int unset_alias(char *name)
{
	AliasData *ptr = alist, *next;

	if (alist == NULL)
		return (0);
	if (ptr -> name == name)
	{
		alist = alist -> next;
		free(ptr -> val);
		free(ptr);
		return (0);
	}
	while (ptr -> next != NULL && ptr -> next-> name != name)
		ptr = ptr -> next;
	if (ptr -> next -> name == name)
	{
		next = ptr -> next -> next;
		free(ptr -> next -> name);
		free(ptr -> next);
		ptr -> next = next;
	}
	return (0);
}
		
int aliascmd(char *av[])
{
	AliasData *ptr = alist;
	int i;
	char *name, *val;

/*	printf("av1 %s ptr %p\n", av[1], ptr);*/
	if (av[1] == NULL)
	{
		while(ptr != NULL)
		{
			printf("%s=%s\n", ptr -> name, ptr-> val);
			ptr = ptr -> next;

		}
		return (0);
	}
	for (i = 1; av[i] != NULL; i++)
	{
		name = strtok(av[1], "=");
		val = strtok(NULL,"=");
		name = _strdup(name);
		if (name == NULL)
			return (-1);
		val = _strdup(val);
		if (val == NULL)
		{
			free(name);
			return (-1);
		}
		return (set_alias(name, val));
	}
	return (1);
}
