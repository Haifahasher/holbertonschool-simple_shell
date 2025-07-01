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

/* Constants */
#define MAX_ARGS 64
#define DELIM " \t\r\n\a"

/* External variable for environment */
extern char **environ;

/* Function prototypes */

/* Main execution functions */
int execute_command(char **args);
void print_error(char *program, char *command);
void free_args(char **args);

/* Utility functions */
char **tokenize(char *line);
char *trim_spaces(char *str);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
int _strlen(char *s);

#endif /* SHELL_H */
