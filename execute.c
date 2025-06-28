#include "shell.h"

/**
 * execute_command - Execute a command using fork and execve
 * @command: The command to execute
 *
 * Description: This function creates a child process to execute
 * the given command. It handles errors and waits for child completion.
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[2];

	/* Prepare arguments for execve */
	argv[0] = command;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		/* Child process */
		if (execve(command, argv, environ) == -1)
		{
			perror(command);
			exit(127);
		}
	}
	else
	{
		/* Parent process */
		wait(&status);
	}
}

/**
 * print_error - Print error message to stderr
 * @program: Name of the program
 * @command: Command that failed
 *
 * Description: Prints formatted error message when command is not found
 */
void print_error(char *program, char *command)
{
	fprintf(stderr, "%s: 1: %s: not found\n", program, command);
}
