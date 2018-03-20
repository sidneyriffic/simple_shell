#include "shell.h"
#define DEBUGSVARS
int parsesetsvar(char **av)
{
	int haseq, i = 0, ac = 0;
	char *ptr, *name, *val;

	do {
		haseq = 0;
		while (av[i] != NULL)
		{
			for (ptr = av[i]; *ptr; ptr++)
				if (*ptr == '=')
				{
					haseq = 1;
					name = strtok(av[i], "=");
					val = strtok(NULL, "");
					setsvar(name, val);
					ac++;
				}
			i++;
		}
	} while (haseq);
	return (ac);
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
		printf("Name got:%s\n::varptr:%s", name, varptr);
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

int parseargs(char **buf)
{
	char *av[1024], *cmd[1024], *ptr;
	int ac, cc, ret = 0, numvarset;
	char *wordd = " ", *cmdd = ";";

	if (*buf[0] == 0)
		return (0);
	*buf = subsvars(buf);
	if (*buf == NULL)
		return (-1);
	for (ptr = *buf; *ptr != 0; ptr++)
		if (*ptr == '#' || *ptr == '\n')
		{
			*ptr = 0;
			break;
		}
	cc = 0;
	cmd[cc++] = strtok(*buf, cmdd);
#ifdef DEBUGMODE
		printf("Got cs %s\n", cmd[cc - 1]);
#endif
	while(cmd[cc - 1] != NULL)
	{
		cmd[cc++] = strtok(NULL, cmdd);
#ifdef DEBUGMODE
		printf("Got cs %s\n", cmd[cc - 1]);
#endif
	}
	cc = 0;
	while (cmd[cc] != NULL)
	{
		ac = 0;
		av[ac++] = strtok(cmd[cc], wordd);
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
		numvarset = parsesetsvar(av);
#ifdef DEBUGMODE
		printf("Calling command/builtin numvarset %d\n", numvarset);
#endif
		ret = builtincall(av + numvarset);
		cc++;
	}
	return (ret);
}
