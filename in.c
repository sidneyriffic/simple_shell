#include "shell.h"

int shintmode()
{
	char *buf;
	int lenr;
	char *prompt = "Homemade shell>";

	buf = malloc(1048576);
	if (buf == NULL)
	{
		perror("Not enough memory to allocate buffer:");
		return (-1);
	}	
	while(1)
	{
		write(1, prompt, 15);
		lenr = read(STDIN_FILENO, buf, 1048576);
		/* handle read error later */
		lenr--;
		buf[lenr] = 0;
		printf("\n---\nbuffer from read %s\nCalling command:\n", buf);
		parseargs(buf);
	}
	return (0);
}

int main(int ac, char *av[])
{
	printf("main av[0] %s av[1] %s\n", av[0], av[1]);
	if (ac > 1)
		return (1);

	return (shintmode(ac, av));
}
