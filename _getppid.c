#include "shell.h"
/**
 *
 *
 *
 */
pid_t getppid(void)
{
	pid_t my_pid;

	my_pid = fork();

	if (my_pid == -1)
	{
		perror("ERROR");
		return(1);
	}
	
