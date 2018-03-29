#ifndef SHELLH
#define SHELLH

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "history.h"
/*#include <string.h>*/

/* from in.c */
int shintmode();

/* from _printenv.c */
int _printenv();

/* from cmdcall.c */
int builtincall(char *av[]);
int cmdcall(char *av[], char *path);

/* from parser.c */
int parseargs(char **buf);
char *tildeexpand(char *buf);

/* from errhandl.c */
int errhandl(int status);

/* from _getenv.c */
char ***getenviron();
int setallenv(char **environ, char *add);
char *_getenv(char *avzero);
int _setenv(char *name, char *val);
int _unsetenv(char *name);
char **getallenv();

/* from string.c */
size_t _strlen(char *str);
char *_strcpy(char *dest, char *src);
int _strcmp(char *, char *);
char *_strdup(char *str);
char *_strcat(char *a, char *b);

/* from utility.c */
char *itos(int digits);
char *_strchr(char *s, char c);
int fprintstrs(int fd, char *str, ...);
int printerr();
int linecount();

/* from cd.c */
int _cd(char *av[]);

/* from alias.c */
int aliascmd(char **av);
char *getalias(char *name);
int unsetalias(char *name);

/* from shellvars.c */
int initsvars(int ac, char **av);
char *getsvar(char *name);
int setsvar(char *name, char *val);
int unsetsvar(char *name);

/* from _realloc.c */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* from _strtok.c */
char *strtok(char *str, char *delim);

/* from _getline.c */
int _getline(char **lineptr, int fd);

char *strtokqe(char *str, char *delim, int escflags);


/* from _printenv.c */
int _printenv();
int _putchar(char c);

/*from history.c*/
int sethist (char *cmd);
int print_hist();
int exit_hist();

/*from help.c*/
int help (char *cmd);

/* from exitcleanup.c */
void exitcleanup();

#endif
