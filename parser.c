#include "shell.h"

char *subsvars(char **buf)
{
	char *varptr = *buf, *ptr, *name, *val, *valptr, *dest;
	size_t buflen = _strlen(*buf);
	size_t varvlen, varnlen, i;

	while (*varptr != 0)
	{
		printf("Top of svar loop buf:%s::varptr:%s\n", *buf, varptr);
		while (*varptr != '$' && *varptr != 0)
			varptr++;
		if (*varptr == 0)
			return (*buf);
		varptr++;
		for (ptr = varptr, varnlen = 0; *ptr != 0 && *ptr != ' '
			     && *ptr != '\n' && *ptr != '$'; ptr++)
			varnlen++;
		printf("varnlen:%d varptr:%s\n", varnlen, varptr);
		name = malloc (sizeof(char) * (varnlen + 1));
		if (name == NULL)
			return (NULL);
		for (i = 0; i < varnlen; i++, varptr++)
			name[i] = *varptr;
		name[i] = 0;
		printf("Name got:%s\n::varptr:%s", name, varptr);
		val = getsvar(name);
		if (val == name)
		{
			val = _strdup("");
		}
		free(name);
		printf("val got:%s\n", val);
		varvlen = _strlen(val);
		/* need new buffer for substituted var string */
		buflen = buflen - varnlen + varvlen + 1;
		printf("malloc size:%d\n", buflen);
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
		printf("Resulting buf:%s::varptr:%s\n", name, varptr);
		free(*buf);
		*buf = name;
	}
	return (*buf);
}

int parseargs(char **buf, char **environ)
{
	char *av[1024], *cmd[1024], *ptr;
	int ac, cc, ret = 0;
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
#ifdef DEBUGMODE
		printf("Calling command/builtin\n");
#endif
		ret = builtincall(av, environ);
		cc++;
	}
	return (ret);
}
