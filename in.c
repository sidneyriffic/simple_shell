#include "shell.h"

/**
 * shintmode - shell interactive mode
 * Return: 0
 */
int shintmode()
{
	char *bufgl = NULL, *pwd;
	char *s;
	ssize_t lenr = 0;
	int istty = isatty(0) && isatty(1);

	while (1)
	{
#ifdef DEBUGMODE
		printf("At terminal prompt\n");
#endif
		if (istty)
		{
			pwd = _getenv("PWD");
			if (pwd != NULL)
			{
				fprintstrs(1, "Homemade shell:", pwd, "$", NULL);
				free(pwd);
			}
			else
			{
				fprintstrs(1, "Homemade shell$", NULL);
			}
		}
		lenr = _getline(&bufgl, STDIN_FILENO);
		/*history begin*/
		history(bufgl);
		/*end history*/
		if ((lenr == 0 && !istty) || lenr == -1)
		{
			free(bufgl);
			break;
		}
#ifdef DEBUGMODE
		printf("calling parseargs %s\n", bufgl);
#endif
		parseargs(&bufgl);
		bufgl = NULL;
	}
	return (0);
}
/**
 * scriptmode - shell script mode
 * @ac: num of arguments
 * @av: arguments
 * Return: 0 upon success or -1 if failure
 */
int scriptmode(int ac, char *av[])
{
	char *buf = NULL;
	int i = 1;
	ssize_t n;
	int infile;

	while (i < ac)
	{
		infile = open(av[i], O_RDONLY);
		/*if (infile == -1)*/
		/*continue;*/
		do {
			n = _getline(&buf, infile);
			if (buf == NULL)
				return (-1); /* fix buffer allocation error later */
			parseargs(&buf);
			buf = NULL;
		} while (n > 0);
		close(infile);
		i++;
	}
	return (0);
}

int main(int ac, char *av[], char **environ)
{
	setbuf(stdout, NULL);
	initsvars(ac, av);
	setallenv(environ, NULL);
#ifdef DEBUGINIT
	printf("?:%s\n", getsvar("?"));
	printf("0:%s\n", getsvar("0"));
	setsvar(_strdup("simplevar"), _strdup("98"));
	printf("simplevar:%s\n", getsvar("simplevar"));
#endif
	if (ac > 1)
		return (scriptmode(ac, av));

	return (shintmode());
}
