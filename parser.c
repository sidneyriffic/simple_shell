#include "shell.h"

/* returns buf after var setting */
char *parsesetsvar(char *buf)
{
	int haseq;
	char *ptr, *name, *val, *bufstart = buf, *newbuf;

	do {
		haseq = 0;
		for (ptr = buf; *ptr; ptr++)
		{
#ifdef DEBUGSVARS
			printf("in loop ptr:%s\n", ptr);
#endif
			if (*ptr == ' ')
				break;
			if (*ptr == '=')
			{
				name = strtok(buf, " ");
				buf = strtok(NULL, "");
				ptr = buf;
				haseq = 1;
				name = strtok(name, "=");
				val = strtok(NULL, "");
#ifdef DEBUGSVARS
				printf("In parsesetvar: setting var %s to %s\n", name, val);
#endif
				setsvar(name, val);
			}
			if (ptr == NULL)
				return (NULL);
		}
	} while (haseq && *ptr != 0);
	newbuf = malloc(_strlen(buf));
	if (newbuf == NULL)
		return (NULL);
	newbuf = _strcpy(newbuf, buf);
	return (newbuf);
}

char *subsvars(char **buf)
{
	char *varptr = *buf, *ptr, *name, *val, *valptr, *dest, *dolptr;
	size_t buflen = _strlen(*buf);
	size_t varvlen, varnlen, i;

#ifdef DEBUGSVARS
	printf("In subsvars\n");
#endif
	while (*varptr != 0)
	{
#ifdef DEBUGSVARS
		printf("Top of svar loop buf:%s::varptr:%s\n", *buf, varptr);
#endif
		while (*varptr != '$' && *varptr != 0)
		{
			if (*varptr == '\\')
			{
				if (*varptr != 0)
					varptr++;
				varptr++;
				continue;
			}
			if (*varptr == '\'')
			{
				varptr++;
				while(*varptr != '\'')
					varptr++;
			}
			varptr++;
		}
#ifdef DEBUGSVARS
		printf("At $:%s\n", varptr);
#endif
		dolptr = varptr;
		if (*varptr == 0)
			return (*buf);
		varptr++;
		for (ptr = varptr, varnlen = 0; *ptr != 0 && *ptr != ' '
			     && *ptr != '\n' && *ptr != '$'; ptr++)
			varnlen++;
#ifdef DEBUGSVARS
		printf("varnlen:%d varptr:%s\n", varnlen, varptr);
#endif
		name = malloc (sizeof(char) * (varnlen + 1));
		if (name == NULL)
			return (NULL);
		for (i = 0; i < varnlen; i++, varptr++)
			name[i] = *varptr;
		name[i] = 0;
#ifdef DEBUGSVARS
		printf("Name got:%s\n::varptr:%s\n", name, varptr);
#endif
		val = _getenv(name);
		if (val == name)
		{
#ifdef DEBUGSVARS
			printf("%s not an env var, checking svars\n", name);
#endif
			val = getsvar(name);
			if (val == name)
				val = _strdup("");
		}
		free(name);
#ifdef DEBUGSVARS
		printf("val got:%s\n", val);
#endif
		varvlen = _strlen(val);
		/* need new buffer for substituted var string */
		buflen = buflen - varnlen + varvlen + 1;
#ifdef DEBUGSVARS
		printf("malloc size:%d\n", buflen);
#endif
		name = malloc(sizeof(char) * (buflen));
		for (ptr = *buf, dest = name, valptr = val; *ptr != 0; ptr++, dest++)
		{
/*		printf("copy to new buf %s::%s\n", ptr, name);*/
			if (val != NULL && ptr == dolptr)
			{
				while (*valptr != 0)
					*dest++ = *valptr++;
				val = NULL;
				varptr = dest;
				ptr += varnlen + 1;
			}
			*dest = *ptr;
		}
		*dest = *ptr;
#ifdef DEBUGSVARS
		printf("Resulting buf:%s::varptr:%s\n", name, varptr);
#endif
/*		free(*buf);*/
		*buf = name;
		setsvar("?", "0");
	}
	return (*buf);
}

char *cleanarg(char *arg)
{
	char *newbuf, *ptr, *ptr2;
	size_t len = 0;
	int inquote = 0;

	ptr = arg;
	while (*ptr != 0)
	{
		if (*ptr == '\\' && !(inquote == 1))
		{
			ptr++;
			if (*ptr != 0)
			{
				len++;
				ptr++;
			}
			continue;
		}
		if (!inquote && *ptr == '"')
		{
			inquote = 2;
			ptr++;
			continue;
		}
		if (!inquote && *ptr == '\'')
		{
			inquote = 1;
			ptr++;
			continue;
		}
		if ((inquote == 1 && *ptr == '\'') || (inquote == 2 && *ptr == '"'))
		{
			inquote = 0;
			ptr++;
			continue;
		}
		if (*ptr == 0)
			break;
		ptr++;
		len++;
	}
	newbuf = malloc(sizeof(char) * (len + 1));
	if (newbuf == NULL)
		return (NULL);
	ptr = arg;
	ptr2 = newbuf;
	inquote = 0;
	while (*ptr != 0)
	{
		if (*ptr == '\\' && !(inquote == 2))
		{
			ptr++;
			if (*ptr != 0)
				*ptr2++ = *ptr++;
			continue;
		}
		if (!inquote && *ptr == '"')
		{
			inquote = 2;
			ptr++;
			continue;
		}
		if (!inquote && *ptr == '\'')
		{
			inquote = 1;
			ptr++;
			continue;
		}
		if ((inquote == 1 && *ptr == '\'') || (inquote == 2 && *ptr == '"'))
		{
			inquote = 0;
			ptr++;
			continue;
		}
		if (*ptr != 0)
			*ptr2++ = *ptr++;
	}
	*ptr2 = 0;
#ifdef DEBUGMODE
	printf("clean arg return buf:%s\n", newbuf);
#endif
	return (newbuf);
}
	
/* double pointer buf so we can free after subbing vars easier */
int parseargs(char **buf)
{
	char *av[1024], *ptr, *left, *right;
	int ac, ret = 0;
	char *wordd = " ", *cmdd = ";";

#ifdef DEBUGMODE
	printf("In parseargs. buf:%s\n", *buf);
#endif
	if (*buf == NULL)
		return (0);
	if (*buf[0] == 0)
		return (0);
	for (ptr = *buf; *ptr != 0; ptr++)
		if (*ptr == '#' || *ptr == '\n')
		{
			*ptr = 0;
			break;
		}
#ifdef DEBUGMODE
	printf("Breaking command segments:%s\n", *buf);
#endif
	left = strtokqe(*buf, ";", 7);
	right = strtokqe(NULL, "", 7);
#ifdef DEBUGMODE
	printf("left cmd %s\n", left);
	printf("right cmd %s\n", right);
#endif
	if (right != NULL && *right != 0)
	{
		parseargs(&left);
		return (parseargs(&right));
	}
#ifdef DEBUGMODE
	printf("Performing logic %s\n", *buf);
#endif
	left = strtokqe(*buf, "|&", 7);
	right = strtokqe(NULL, "", 7);
#ifdef DEBUGMODE
	printf("left cmd %s\n", left);
	printf("right cmd %s\n", right);
#endif
	if (right != NULL && *right == '&')
	{
		ret = parseargs(&left);
		right++;
		if (ret == 0)
			return (parseargs(&right));
		else
		{
			strtokqe(right, "|", 7);
			right = strtokqe(NULL, "", 7);
			return (parseargs(&right));
		}
	}
	if (right != NULL && *right == '|')
	{
		ret = parseargs(&left);
		right++;
		if (ret == 0)
			return (1);
		return (parseargs(&right));
	}
#ifdef DEBUGMODE
	printf("Subbing vars %s\n", *buf);
#endif
	*buf = subsvars(buf);
	if (*buf == NULL)
		return (-1);
#ifdef DEBUGMODE
	printf("Setting vars %s\n", *buf);
#endif
	*buf = parsesetsvar(*buf);
	if (*buf == NULL)
		return (0);
	ac = 0;
	av[ac++] = strtokqe(*buf, wordd, 7);
#ifdef DEBUGMODE
	printf("Got arg %s\n", av[ac - 1]);
#endif
	av[0] = getalias(av[0]);
#ifdef DEBUGMODE
	printf("Alias:%s\n", av[0]);
#endif
	if (av[0] != NULL)
		av[0] = cleanarg(av[0]);
#ifdef DEBUGMODE
		printf("Clean arg %s\n", av[0]);
#endif
	while (av[ac - 1] != NULL)
	{
		av[ac] = strtokqe(NULL, wordd, 7);
#ifdef DEBUGMODE
		printf("Got arg %s\n", av[ac]);
#endif
		if (av[ac] != NULL)
			av[ac] = cleanarg(av[ac]);
#ifdef DEBUGMODE
		printf("Clean arg %s\n", av[ac]);
#endif
		ac++;
	}
	ac--;
	av[ac] = NULL;
	ret = builtincall(av);
	return (ret);
}
