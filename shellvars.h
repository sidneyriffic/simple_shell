#ifndef SHELLVARH
#define SHELLVARH

/**
 * struct ShellVar - shellvar list node
 *
 * @name: name of var
 * @val: value of var
 * @next: next var in list
 */
typedef struct ShellVar
{
	char *name;
	char *val;
	struct ShellVar *next;
} ShellVar;

#endif
