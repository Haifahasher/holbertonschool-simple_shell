#include "shell.h"

/**
 * main - Entry point for simple shell
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;
	int status = 0;
	char *trimmed_line; /* New variable for line after trimming */

	while (1)
	{
		/* Print prompt only if stdin is a terminal */
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "$ ", 2);
		}

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			/* Handle Ctrl+D (EOF) */
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Remove newline character */
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		/* Trim spaces from the line - keep original pointer */
		trimmed_line = trim_spaces(line);

		/* Skip empty lines or lines with only spaces */
		if (trimmed_line == NULL || trimmed_line[0] == '\0')
			continue;

		/* Tokenize the input into command and arguments */
		args = tokenize(trimmed_line);
		if (args == NULL || args[0] == NULL)
		{
			free_args(args);
			continue;
		}

		/* Check for exit command */
		if (_strcmp(args[0], "exit") == 0)
		{
			free_args(args);
			break;
		}

		/* Execute the command */
		status = execute_command(args);
		free_args(args); /* Use dedicated function to free memory */
	}

	free(line); /* Free only the original pointer */
	return (status);
}
