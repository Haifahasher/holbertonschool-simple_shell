#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

extern char **environ;

void prompt(void);
char *read_line(void);
char **split_line(char *line);
int execute(char **args, char *argv0, int line_count);
int handle_builtin(char **args);
char *find_path(char *command);
void print_env(void);

#endif /* SHELL_H */
