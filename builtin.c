#include "shell.h"

/**
 * handle_builtin - Checks and executes built-in commands
 * @args: Argument array
 * Return: 1 if a built-in was handled, 0 otherwise
 */
int handle_builtin(char **args)
{
	if (strcmp(args[0], "exit") == 0)
		exit(0);
	if (strcmp(args[0], "env") == 0)
	{
		print_env();
		return (1);
	}
	return (0);
}

/**
 * print_env - Prints the environment variables
 */
void print_env(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
