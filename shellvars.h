#ifndef SHELLVARH
#define SHELLVARH

typedef struct ShellVar
{
	char *name;
	char *val;
	struct ShellVar *next;
} ShellVar;

#endif
