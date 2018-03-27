#include "shell.h"
int help(char *cmd)
{
	char *file;
	int total = 0;
	int fd, r;
	char *s;
	if (!_strcmp(cmd, "cd"))
	{
		file = "help_cd";
		fd = open(file, O_RDWR);
		s = malloc(1024);
		if (s == NULL)
			return (-1);
		while ((r = read(fd, &s, 1024)) > 0)
		{
			r = write (1, &s, r);
			if  (r == -1)
			{
				exit(99);
			}
			total = total + r;
		}
		*s = 0;
		free(s);
		return(total);
	}
	else if (!_strcmp(cmd, "alias"))
	{
		file = "help_al";
		fd = open(file, O_RDWR);
		s = malloc(1024);
		if (s == NULL)
			return (-1);
		while ((r = read(fd, &s, 1024)) > 0)
		{
			r = write (1, &s, r);
			if  (r == -1)
			{
				exit(99);
			}
			total = total + r;
		}
		*s = 0;
		free(s);
		return(total);
	}
	else if (!_strcmp(cmd, "history"))
	{
		file = "help_hist";
		fd = open(file, O_RDWR);
		s = malloc(1024);
		if (s == NULL)
			return (-1);
		while ((r = read(fd, &s, 1024)) > 0)
		{
			r = write (1, &s, r);
			if  (r == -1)
			{
				exit(99);
			}
			total = total + r;
		}
		*s = 0;
		free(s);
		return(total);
	}
	else if (!_strcmp(cmd, "help"))
	{
		file = "help_hel";
		fd = open(file, O_RDWR);
		s = malloc(1024);
		if (s == NULL)
			return (-1);
		while ((r = read(fd, &s, 1024)) > 0)
		{
			r = write (1, &s, r);
			if  (r == -1)
			{
				exit(99);
			}
			total = total + r;
		}
		*s = 0;
		free(s);
		return(total);
	}
		fd = close(fd);
}
