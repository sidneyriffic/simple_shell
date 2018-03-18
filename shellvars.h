#ifndef ALIASH
#define ALIASH

typedef struct ShellVar
{
	char *name;
	char *val;
	struct ShellVar *next;
} ShellVar;

#endif
