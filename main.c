#include "shell.h"

/**
 * main - Entry point of the shell
 *
 * Return: 0 on success, 1 on error
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *argv[64];
	int i;
	pid_t pid;
	int status;

	while (1)
	{
		write(STDOUT_FILENO, "($) ", 4);

		nread = getline(&line, &len, stdin);
		if (nread == -1) /* Ctrl+D or EOF */
		{
			free(line);
			write(STDOUT_FILENO, "\n", 1);
			return (0);
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		argv[0] = strtok(line, " ");
		if (!argv[0]) /* Empty input */
			continue;

		for (i = 1; i < 63; i++)
		{
			argv[i] = strtok(NULL, " ");
			if (!argv[i])
				break;
		}
		argv[i] = NULL;

		pid = fork();
		if (pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
			{
				perror("hsh");
				free(line);
				exit(1);
			}
		}
		else if (pid > 0)
			wait(&status);
		else
		{
			perror("hsh");
			free(line);
			return (1);
		}
	}

	free(line);
	return (0);
}
