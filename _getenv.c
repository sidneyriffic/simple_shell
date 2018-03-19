#include "shell.h"

char **environ;

char **getallenv()
{
	char **envcopy;
	size_t len = 0;

	envcopy = environ;
	while (envcopy[len] != NULL)
		len++;
#ifdef DEBUGMODE
	printf("Got length of env lines %d\nNow copying\n", len);
#endif
	envcopy = malloc(sizeof(char **) * (len + 1));
	if (envcopy == NULL)
		return (NULL);
	while (len > 0)
	{
		envcopy[len] = environ[len];
		len--;
	}
	envcopy[len] = environ[len];
	return (envcopy);
}

/* add should be null for first init to not free passed array */
int setallenv(char **envin, char *newval)
{
	size_t len = 0;

#ifdef DEBUGMODE
	printf("In setallenv, newval:%s\n", newval);
#endif
	while (envin[len] != NULL)
		len++;
	if (newval != NULL)
		len++;
	environ = malloc(sizeof(char **) * (len + 1));
	if (environ == NULL)
		return (-1);
	for (len = 0; envin[len] != NULL; len++)
		environ[len] = envin[len];
	if (newval != NULL)
	{
#ifdef DEBUGMODE
		printf("Adding newval:%s\n", newval);
#endif
		environ[len] = newval;
		len++;
	}
	environ[len] = 0;
#ifdef DEBUGMODE
	printf("At end. Free old environ if adding a string\n");
#endif
	if (newval != NULL)
		free(envin);
	return (0);
}

char *_getenv(char *name)
{
	int i, j;
	char *s;

#ifdef DEBUGMODE
	printf("In getenv, name:%s\n", name);
#endif
	i = 0;
	while (environ[i] != NULL)
	{
		s = environ[i];
		j = 0;
#ifdef DEBUGMODE
		printf("Checking against:%s\n", environ[i]);
#endif
		while (s[j] == name[j])
		{
			j++;
			if (name[j] == 0 && s[j] == '=')
				return (_strdup(s + j + 1));
		}
		i++;
	}
	return(name);
}

int _setenv(char *name, char *val)
{
	int i, j, namel, vall;
	char *s, *ptr;

#ifdef DEBUGMODE
	printf("In setenv, name:%s\n", name);
#endif
	if (name == NULL || val == NULL)
		return (0);
	namel = _strlen(name);
	vall = _strlen(val);
	i = 0;
	ptr = malloc(sizeof(char) * (namel + vall + 2));
	if (ptr == NULL)
		return (-1);
	s = ptr;
	_strcpy(s, name);
	s += namel;
	_strcpy(s++, "=");
	_strcpy(s, val);
	s += vall + 1;
	*s = 0;
#ifdef DEBUGMODE
	printf("Ptr mallocd:%s\n", ptr);
#endif
	while (environ[i] != NULL)
	{
		s = environ[i];
		j = 0;
		while (s[j] == name[j])
		{
			j++;
			if (name[j] == 0 && s[j] == '=')
			{
				free(s);
				environ[i] = ptr;
				return (0);
			}
		}
		i++;
	}
	return (setallenv(environ, ptr));
}
