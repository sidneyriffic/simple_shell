#include "shell.h"
#define DEBUGMODE
#define DEBUGSVARS

/* returns new buf after var setting */
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
			{
#ifdef DEBUGSVARS
				printf("No other args found, returning\n");
#endif
				free(bufstart);
				return (NULL);
			}
		}
	} while (haseq && *ptr != 0);
	newbuf = malloc(sizeof(char) * (_strlen(buf) + 1));
	if (newbuf == NULL)
		return (NULL);
	newbuf = _strcpy(newbuf, buf);
	free(bufstart);
	return (newbuf);
}

char *subsvars(char **buf)
{
	char *varptr = *buf, *ptr, *name, *val, *valptr, *dest, *dolptr;
	size_t buflen = _strlen(*buf);
	size_t varvlen, varnlen, i;
	int inquotes = 0;

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
			printf("inquotes:%d:varptr:%s\n", inquotes, varptr);
			if (*varptr == '\\')
			{
				varptr++;
				if (*varptr != 0)
					varptr++;
				continue;
			}
			if (inquotes == 2 && *varptr == '"')
				inquotes = 0;
			if (inquotes == 0 && *varptr == '"')
				inquotes = 2;
			if (*varptr == '\'' && inquotes != 2)
			{
				varptr++;
				/* change this later to read more stdin if 
				 * single quote not matched */
				while(*varptr != '\'' && *varptr != 0)
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
				free(val);
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
		free(*buf);
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
		if (*ptr == '\\' && !inquote)
		{
			ptr++;
			if (*ptr != 0)
			{
				len++;
				ptr++;
			}
			continue;
		}
		if (*ptr == '\\' && inquote == 2)
		{
			ptr++;
			if (*ptr == '$' || *ptr == '#' || *ptr == ';' || *ptr =='\\')
			{
				len++;
				ptr++;
			}
			else
				len++;
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
		if (*ptr == '\\' && !inquote)
		{
			ptr++;
			if (*ptr != 0)
				*ptr2++ = *ptr++;
			continue;
		}
		if (*ptr == '\\' && inquote == 2)
		{
			ptr++;
			if (*ptr == '$' || *ptr == '#' || *ptr == ';' || *ptr == '\\')
				*ptr2++ = *ptr++;
			else
				*ptr2++ = '\\';
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
	free(arg);
	return (newbuf);
}
	
/* double pointer buf so we can free after subbing vars easier
 * frees buf at end */
int parseargs(char **buf)
{
	char *av[1024], *ptr, *left, *right;
	int ac, ret = 0;
	char *wordd = " ";

#ifdef DEBUGMODE
	printf("In parseargs. buf:%s\n", *buf);
#endif
	if (*buf == NULL)
		return (0);
	for (ptr = *buf; *ptr != 0; ptr++)
		if (*ptr == '#' || *ptr == '\n')
		{
			*ptr = 0;
			break;
		}
	if (*buf[0] == 0)
	{
		free (*buf);
		return (0);
	}
#ifdef DEBUGMODE
	printf("Breaking command segments:%p:%s\n", *buf, *buf);
#endif
	left = _strdup(strtokqe(*buf, ";", 7));
	right = _strdup(strtokqe(NULL, "", 7));
	printf("buf:%p:%s:left:%p:%s:right:%p:%s:\n", *buf, *buf, left, left, right, right);
	free(*buf);
	*buf = left;
#ifdef DEBUGMODE
	printf("left cmd %s\n", left);
	printf("right cmd %s\n", right);
#endif
	if (right != NULL && *right != 0)
	{
		parseargs(&left);
		*buf = right;
		return (parseargs(&right));
	}
#ifdef DEBUGMODE
	printf("Performing logic %s\n", *buf);
#endif
	left = _strdup(strtokqe(*buf, "|&", 7));
	right = _strdup(strtokqe(NULL, "", 7));
	free(*buf);
	*buf = left;
#ifdef DEBUGMODE
	printf("left cmd %s\n", left);
	printf("right cmd %s\n", right);
#endif
	if (right != NULL && *right == '&')
	{
		ret = parseargs(&left);
		free(left);
		*buf = right;
		right++;
		right = _strdup(right);
		free(*buf);
		if (ret == 0)
			return (parseargs(&right));
		else
		{
			*buf = right;
			strtokqe(right, "|", 7);
			right = strtokqe(NULL, "", 7);
			if (right != NULL)
			{
				right++;
				right = _strdup(right);
				free(*buf);
				return (parseargs(&right));
			}
			else
			{
				free(*buf);
				return (ret);
			}
		}
	}
	if (right != NULL && *right == '|')
	{
		ret = parseargs(&left);
		left = right;
		right++;
		right = _strdup(right);
		free(left);
		if (ret == 0)
		{
			free(right);
			return (1);
		}
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
	av[ac++] = _strdup(strtokqe(*buf, wordd, 7));
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
	printf("Clean arg[%d] %s\n", ac - 1, av[ac - 1]);
#endif
	while (av[ac - 1] != NULL)
	{
		av[ac] = _strdup(strtokqe(NULL, wordd, 7));
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
#ifdef DEBUGMODE
	printf("After cmdcall ret:%d\n", ret);
#endif
	free(*buf);
	*buf = NULL;
#ifdef DEBUGMODE
	printf("Free av strings\n");
#endif
	for (ac = 0; av[ac] != NULL; ac++)
		free(av[ac]);
#ifdef DEBUGMODE
	printf("Returning, ret:%d\n", ret);
#endif
	return (ret);
}
