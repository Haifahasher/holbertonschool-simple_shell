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

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			/* Handle Ctrl+D (EOF) */
			printf("\n");
			break;
		}

		/* Remove newline character */
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		/* Skip empty lines */
		if (line[0] == '\0')
			continue;

		/* Check for exit command */
		if (_strcmp(line, "exit") == 0)
			break;

		/* Execute the command */
		execute_command(line);
	}

	free(line);
	return (0);
}
