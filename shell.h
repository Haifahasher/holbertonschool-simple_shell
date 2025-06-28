#ifndef SHELL_H
#define SHELL_H

/* Standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

/* External variable for environment */
extern char **environ;

/* Function prototypes */

/* Main execution functions */
void execute_command(char *command);
void print_error(char *program, char *command);

/* Utility functions */
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
int _strlen(char *s);

#endif /* SHELL_H */
