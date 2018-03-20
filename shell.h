#ifndef SHELLH
#define SHELLH

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/* from in.c */
int shintmode();

/* from cmdcall.c */
int builtincall(char *av[]);
int cmdcall(char *av[]);

/* from parser.c */
int parseargs(char **buf);

/* from errhandl.c */
int errhandl(int status);

/* from _getenv.c */
int setallenv(char **environ, char *add);
char *_getenv(char *avzero);
int _setenv(char *name, char *val);
char **getallenv();

/* from string.c */
size_t _strlen(char *str);
char *_strcpy(char *dest, char *src);
int _strcmp(char *, char *);
char *_strdup(char *str);

/* from utility.c */
char *itos(int digits);

/* from cd.c */
int _cd(char *av[]);

/* from alias.c */
int aliascmd(char **av);
char *getalias(char *name);

/* from shellvars.c */
int initsvars(int ac, char **av);
char *getsvar(char *name);
int setsvar(char *name, char *val);

#endif
