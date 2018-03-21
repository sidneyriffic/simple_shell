#include "shell.h"
#define DEBUGMODE
#define DEBUGSVARS

/* returns buf after var setting */
char *parsesetsvar(char *buf)
{
	int haseq;
	char *ptr, *name, *val, *bufstart = buf, *newbuf;

	do {
		haseq = 0;
		for (ptr = buf; *ptr; ptr++)
		{
			printf("in loop ptr:%s\n", ptr);
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
			printf("in loop ptr:%s\n", ptr);
			if (ptr == NULL)
				return (NULL);
		}
	} while (haseq && *ptr != 0);
	printf("ool buf:%s\n", buf);
	newbuf = malloc(_strlen(buf));
	if (newbuf == NULL)
		return (NULL);
	printf("mallocd\n");
	newbuf = _strcpy(newbuf, buf);
	return (newbuf);
}

char *subsvars(char **buf)
{
	char *varptr = *buf, *ptr, *name, *val, *valptr, *dest;
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
			varptr++;
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
			/*printf("copy to new buf %s::%s\n", ptr, name);*/
			if (val != NULL && *ptr == '$')
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
		free(*buf);
		*buf = name;
	}
	return (*buf);
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
	if (*buf[0] == 0)
		return (0);
	for (ptr = *buf; *ptr != 0; ptr++)
		if (*ptr == '#' || *ptr == '\n')
		{
			*ptr = 0;
			break;
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
	left = strtok(*buf, cmdd);
	right = strtok(NULL, cmdd);
	printf("left cmd %s\n", left);
	printf("right cmd %s\n", right);
	if (right != NULL && *right != 0)
	{
		parseargs(&left);
		return (parseargs(&right));
	}
#ifdef DEBUGMODE
	printf("Performing logic %s\n", *buf);
#endif
	
	ac = 0;
	av[ac++] = strtok(*buf, wordd);
#ifdef DEBUGMODE
	printf("Got arg %s\n", av[ac - 1]);
#endif
	av[0] = getalias(av[0]);
#ifdef DEBUGMODE
	printf("Alias:%s\n", av[0]);
#endif
	while (av[ac - 1] != NULL)
	{
		av[ac++] = strtok(NULL, wordd);
#ifdef DEBUGMODE
		printf("Got arg %s\n", av[ac -1]);
#endif
	}
	ac--;
	av[ac] = NULL;
	ret = builtincall(av);
	return (ret);
}
