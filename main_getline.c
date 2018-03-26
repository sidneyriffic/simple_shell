#include "shell.h"
void main(int ac, char **av)
{
	char *buf = NULL;
	int len = 0;
	char *file = av[1];

	len = _getline(&buf, STDIN_FILENO);
	printf("%s\n", buf);
	printf("%i\n", len);
	len = _getline(&buf, STDIN_FILENO);
	printf("%s\n", buf);
	printf("%i\n", len);
	len = _getline(&buf, STDIN_FILENO);
	printf("%s\n", buf);
	printf("%i\n", len);
	len = _getline(&buf, STDIN_FILENO);
	printf("%s\n", buf);
	printf("%i\n", len);
	len = _getline(&buf, STDIN_FILENO);
	printf("%s\n", buf);
	free (buf);
	/*
	printf("EOF %d\n", EOF);
	buf = _getline(file);
	printf("%s\n", buf);
	buf = _getline(file);
	printf("%s\n", buf);
	buf = _getline(file);
	printf("%s\n", buf);
	buf = _getline(file);
	printf("%s\n", buf);
	buf = _getline(file);
	printf("%s\n", buf);
	buf = _getline(file);
	printf("%s\n", buf);
	buf = _getline(file);
	printf("%s\n", buf);
	buf = _getline(file);
	printf("%s\n", buf);
	buf = _getline(file);
	printf("%s\n", buf);
	buf = _getline(file);
	printf("%s\n", buf);
	free(buf);

// ACTUAL GETLINE TESTING
	len = getline(&buf, &len, stdin);
	printf("%s\n", buf);
	printf("%i\n", len);
	len = getline(&buf, &len, stdin);
	printf("%s\n", buf);
	printf("%i\n", len);
		len = getline(&buf, &len, stdin);
	printf("%s\n", buf);
	printf("%i\n", len);
		len = getline(&buf, &len, stdin);
	printf("%s\n", buf);
	printf("%i\n", len);
		len = getline(&buf, &len, stdin);
	printf("%s\n", buf);
	printf("%i\n", len);
		len = getline(&buf, &len, stdin);
	printf("%s\n", buf);
	printf("%i\n", len);
		len = getline(&buf, &len, stdin);
	printf("%s\n", buf);
	printf("%i\n", len);
		len = getline(&buf, &len, stdin);
	printf("%s\n", buf);
	printf("%i\n", len);
/*	getline(&buf, &len, stdin);
	printf("%s\n", buf);
	getline(&buf, &len, stdin);
	printf("%s\n", buf);
	getline(&buf, &len, stdin);
	printf("%s\n", buf);
*/
}
