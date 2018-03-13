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
int shintmode(char **environ);

/* from cmdcall.c */
int builtincall(char *av[], char **environ);
int cmdcall(char *av[], char **environ);

/* from parser.c */
int parseargs(char *buf, char **environ);

/* from errhandl.c */
int errhandl(int status);

#endif
