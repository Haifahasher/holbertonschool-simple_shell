#include "shell.h"
#include <stdio.h>

/**
 * print_environ - prints the current environment, one variable per line
 */
void print_environ(void)
{
	char **env = environ;
	while (*env)
	{
		puts(*env);
		env++;
	}
}
