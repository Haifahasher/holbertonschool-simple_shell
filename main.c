#include "shell.h"

/**
 * main - Entry point for the shell
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success, otherwise 1
 */
int main(int ac, char **av)
{
	char *line = NULL, **args = NULL;
	int status = 1, line_count = 0;
	(void)ac;

	while (status)
	{
		if (isatty(STDIN_FILENO))
			prompt();
		line = read_line();
		if (!line)
			break;
		line_count++;
		args = split_line(line);
		if (!args || !args[0])
		{
			free(line);
			free(args);
			continue;
		}
		int builtin_status = handle_builtin(args);

		if (builtin_status)
		{
			free(line);
			free(args);
			if (builtin_status == -1)
				exit(0);
			continue;
		}
		status = execute(args, av[0], line_count);
		free(line);
		free(args);
		if (status != 1)
			return (status);
	}
	return (0);
}
