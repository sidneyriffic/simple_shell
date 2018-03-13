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
int parseargs(char *buf);

/* from errhandl.c */
int errhandl(int status);

#endif
