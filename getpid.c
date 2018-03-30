#include "shell.h"
#include <dirent.h>

/*
char *_getpid
{
	char *s;
	char *pid;
	int fd, i;
	char *name;
	char *file = "/proc/self/status";
	s = malloc(256);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return(0);

	while (_getline(&s, fd))
	{
		name = strtok(s, ":");
		if(!_strcmp(name, "Pid"))
		{
			pid = _strdup(strtok(NULL, "\n \t"));
			free(s);
			return(pid);
		}
		free(s);
		s = NULL;
	}
	return(NULL);
}
*/
