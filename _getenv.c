#include "shell.h"

char *_getenv(char *name)
{
	int i, j;
	char *s;

	i = 0;
	while (environ[i] != NULL)
	{
		s = environ[i];
		j = 0;
		while (s[j] == name[j])
		{
			j++;
			if (name[j] == 0 && s[j] == '=')
				return (s + j + 1);
		}
		i++;
	}
	return(NULL);
}

int _setenv(char *name, char *val, char **environ)
{
	int i, j, namel, vall;
	char *s, *ptr;

	if (name == NULL || val == NULL)
		return (0);
	namel = _strlen(name);
	vall = _strlen(val);
	i = 0;
	while (environ[i] != NULL)
	{
		s = environ[i];
		j = 0;
		while (s[j] == name[j])
		{
			j++;
			if (name[j] == 0 && s[j] == '=')
			{
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
				environ[i] = ptr;
			}
		}
		i++;
	}
	return(1);
}
