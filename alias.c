#include "shell.h"
#include "alias.h"

AliasData *alist;

/* returns original argument if not found */
char *getalias(char *name)
{
	AliasData *ptr = alist;

	while (ptr != NULL && _strcmp(ptr -> name, name))
	{
#ifdef DEBUGMODE
		printf("Checked .%s. against .%s.\n", name, ptr -> name);
#endif
		ptr = ptr -> next;
	}
	if (ptr == NULL)
	{
#ifdef DEBUGMODE
		printf("Alias not found %s\n", name);
#endif
		return (name);
	}
#ifdef DEBUGMODE
	printf("Returning alias %s\n", ptr -> val);
#endif
	return (ptr -> val);
}

int setalias(char *name, char *val)
{
	AliasData *ptr = alist, *new;

	if (alist == NULL)
	{
		new = malloc(sizeof(AliasData));
		if (new == NULL)
			return (-1);
		new -> name = name;
		new -> val = val;
		new -> next = NULL;
		alist = new;
		return (0);
	}
	while (_strcmp(ptr -> name, name) && ptr -> next != NULL)
		ptr = ptr -> next;
	if (!_strcmp(ptr -> name, name))
	{
		free(ptr -> val);
		ptr -> val = val;
		free(name);
	}
	else
	{
		new = malloc(sizeof(AliasData));
		if (new == NULL)
			return (-1);
		new -> name = name;
		new -> val = val;
		new -> next = NULL;
		ptr -> next = new;
	}
	return (0);
}

int unsetalias(char *name)
{
	AliasData *ptr = alist, *next;

	if (alist == NULL)
		return (0);
	if (!(_strcmp(ptr -> name, name)))
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

#ifdef DEBUGMODE
	printf("av1 %p ptr %p\n", av[1], ptr);
	printf("av1 %s\n", av[1]);
#endif
	if (av[1] == NULL)
	{
		while(ptr != NULL)
		{
			printf("%s=%s\n", ptr -> name, ptr-> val);
			ptr = ptr -> next;

		}
		return (0);
	}
#ifdef DEBUGMODE
	printf("Not blank args\n");
#endif
	for (i = 1; av[i] != NULL; i++)
	{
#ifdef DEBUGMODE
		printf("Setting alias %s\n", av[i]);
#endif
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
		return (setalias(name, val));
	}
	return (1);
}
