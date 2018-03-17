#include "shell.h"

int shintmode(char **environ)
{
	char *bufgl;
	size_t bufgllen;
	ssize_t lenr;
	int istty = isatty(0) && isatty(1);

	while(1)
	{
		if (istty)
			printf("Homemade shell:%s$", _getenv("PWD"));
		lenr = getline(&bufgl, &bufgllen, stdin);
		if (lenr == 0 || lenr == -1)
			break;
		parseargs(bufgl, environ);
	}
	return (0);
}

int scriptmode(int ac, char *av[], char **environ)
{
	char *buf = NULL;
	size_t n = 0;
	int i = 1;
	FILE *infile;

	while (i < ac)
	{
		infile = fopen(av[i], "r");
/*		if (infile == -1)
		continue;*/
		do
		{
			if (getline(&buf, &n, infile) == -1)
				break;
			if (buf == NULL)
				return (-1); /* fix buffer allocation error later */
			parseargs(buf, environ);
		} while (*buf != 0);
		fclose(infile);
		i++;
	}
	if (buf != NULL)
		free(buf);
	return (0);
}

int main(int ac, char *av[], char **environ)
{
	if (ac > 1)
		return (scriptmode(ac, av, environ));

	return (shintmode(environ));
}
