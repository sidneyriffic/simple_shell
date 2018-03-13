#include "shell.h"

int shintmode(char **environ)
{
	char buf[1048576];
	char *bufgl;
	size_t bufgllen;
	ssize_t lenr;
	char *prompt = "Homemade shell>";

	while(1)
	{
		write(1, prompt, 15);
		lenr = getline(&bufgl, &bufgllen, stdin);
		if (lenr == 0 || lenr == -1)
			break;
		lenr--;
		buf[lenr] = 0;
		printf("\n---\nbuffer from read %s\nCalling command:\n", buf);
		parseargs(bufgl, environ);
	}
	return (0);
}

int scriptmode(int ac, char *av[], char **environ)
{
	char *buf = NULL;
	size_t n = 0;
	int i = 1, retchk;
	FILE *infile;

	printf("In script mode\n");
	while (i < ac)
	{
		infile = fopen(av[i], "r");
/*		if (infile == -1)
		continue;*/
		do
		{
			printf("In script loop\n");
			if (getline(&buf, &n, infile) == -1)
				break;
			if (buf == NULL)
				return (-1); /* fix buffer allocation error later */
			printf("buff got:%s\n", buf);
			parseargs(buf, environ);
		} while (*buf != 0);
		fclose(infile);
		i++;
		printf("%d %d\n", i, ac);
	}
	if (buf != NULL)
		free(buf);
	return (0);
}

int main(int ac, char *av[], char **environ)
{
	printf("main av[0] %s av[1] %s\n", av[0], av[1]);
	if (ac > 1)
		return (scriptmode(ac, av, environ));

	return (shintmode(environ));
}
