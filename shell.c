#include "shell.h"

/**
 * prompt - Displays the shell prompt
 */
void prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}

/**
 * read_line - Reads a line from stdin
 * Return: Pointer to the line, or NULL on EOF
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/**
 * split_line - Splits a line into tokens (arguments)
 * @line: The input line
 * Return: Array of tokens
 */
char **split_line(char *line)
{
	char *token = NULL, **tokens = NULL;
	int bufsize = 64, i = 0;

	tokens = malloc(sizeof(char *) * bufsize);
	if (!tokens)
		return (NULL);
	token = strtok(line, " \t\r\n");
	while (token)
	{
		tokens[i++] = token;
		if (i >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, sizeof(char *) * bufsize);
			if (!tokens)
				return (NULL);
		}
		token = strtok(NULL, " \t\r\n");
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * execute - Executes a command
 * @args: Argument array
 * @argv0: Program name
 * @line_count: Line number for error
 * Return: 1 to continue, 0 to exit
 */
int execute(char **args, char *argv0, int line_count)
{
	pid_t pid;
	int status;
	char *cmd = NULL;

	cmd = find_path(args[0]);
	if (!cmd)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", argv0, line_count, args[0]);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		execve(cmd, args, environ);
		perror(argv0);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
		if (cmd != args[0])
			free(cmd);
		return (1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (cmd != args[0])
			free(cmd);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (1);
	}
}
