#include "shell.h"

/* complete is bit flag type to complete. 0 none, 1 single quote, 2 double quote, 4 logic,
 * 8 is start of an input or ; separated command. first call should be 8 since we're starting
 * a new input
 * fd is fd we used to get input the first time */
int inputvalidator(char **buf, int fd)
{
	char *newbuf, *bufgl, *bufptr = *buf;
	ssize_t lenr;
	size_t lenbuf;
	int start = 1;
	int complete = 0;

	if (*bufptr == 0)
		return (0);
	while (*bufptr)
	{
#ifdef DEBUGVALID
		printf("In valid loop complete:%d:bufptr:%s", complete, bufptr);
#endif
		while ((*bufptr == ' ' || *bufptr == '\n') && !(complete & 3))
			bufptr++;
		if (*bufptr == 0)
			break;
		if (start)
		{
			if (*bufptr == ';')
			{
				if (bufptr == *buf)
					printerr(": syntax error near unexpected token `;'\n");
				else
					if (*(bufptr - 1) == ';')
						printerr(": syntax error near unexpected token `;;'\n");
					else
						printerr(": syntax error near unexpected token `;\n");
				setsvar("0", "2");
				return (2);
			}
			if (*bufptr == '&' && *(bufptr + 1) == '&')
			{
				printerr(": syntax error near unexpected token `&&'\n");
				setsvar("0", "2");
				return (2);
			}
			if (*bufptr == '|' && *(bufptr + 1) == '|')
			{
				printerr(": syntax error near unexpected token `||'\n");
				setsvar("0", "2");
				return (2);
			}
			start = 0;
		}
		if (bufptr[0] == '\n' && bufptr[1] == 0)
			break;
		if (*bufptr == '#' && !(complete & 3))
		{
			*bufptr = 0;
			break;
		}
		complete &= ~4;
#ifdef DEBUGVALID
		printf("!(complete&3):%d\n", !(complete&3));
#endif
		if (*bufptr == '"' && !(complete & 3))
		{
			complete |= 2;
			bufptr++;
			continue;
		}
		if (*bufptr == '"' && complete & 2)
			complete &= ~2;
		if (*bufptr == '\'' && !(complete & 3))
		{
			complete |= 1;
			bufptr++;
			continue;
		}
		if (*bufptr == '\'' && complete & 1)
			complete &= ~1;
		if (((bufptr[0] == '&' && bufptr[1] == '&') && !(complete & 3)))
		{
			if (bufptr[2] == '&')
			{
				printerr(": syntax error near unexpected token `&'");
				setsvar("0", "2");
				return (2);
			}
			complete |= 4;
			bufptr++;
		}	
		if (((bufptr[0] == '|' && bufptr[1] == '|')) && !(complete & 3))
		{
			if (bufptr[2] == '|')
			{
				printerr(": syntax error near unexpected token `|'\n");
				setsvar("0", "2");
				return (2);
			}
			complete |= 4;
			bufptr++;
		}
		if (*bufptr == ';')
			start = 1;
		bufptr++;
	}
#ifdef DEBUGVALID
	printf("out of while complete:%d\n", complete);
#endif
	if (complete & 7)
	{
#ifdef DEBUGVALID
		printf("not complete:%d", complete);
#endif
		bufgl = NULL;
		if (isatty(fd))
			fprintstrs(1, ">", NULL);
		lenr = _getline(&bufgl, fd);
		if (lenr == 0 && !isatty(fd))
		{
			free(bufgl);
			printerr(": Syntax error: unterminated quoted string\n");
			return (-1);
		}
		if (lenr == -1)
			;/* do something here if getline fails */
		lenbuf = _strlen(*buf);
		newbuf = malloc(lenbuf + lenr + 1);
		/* check malloc fail here */
		_strcpy(newbuf, *buf);
		_strcpy(newbuf + lenbuf, bufgl);
		free(*buf);
		free(bufgl);
#ifdef DEBUGVALID
		printf("Passing buf:%s\n", newbuf);
#endif
		return (inputvalidator(&newbuf, fd));
	}
#ifdef DEBUGVALID
	printf("Final buf:%s\n", *buf);
#endif
	return (parseargs(buf));
}

/**
 * shintmode - shell interactive mode
 * Return: 0
 */
int shintmode()
{
	char *bufgl = NULL, *pwd;
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
		if ((lenr == 0 && !istty) || lenr == -1)
		{
			free(bufgl);
			break;
		}
#ifdef DEBUGMODE
		printf("calling parseargs %s\n", bufgl);
#endif
		inputvalidator(&bufgl, STDIN_FILENO);
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
