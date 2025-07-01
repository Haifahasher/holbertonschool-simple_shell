#include "shell.h"

/**
 * free_args - Free memory allocated for arguments array
 * @args: Array of strings to free
 *
 * Description: Frees each string in the array and then the array itself
 */
void free_args(char **args)
{
	int i;

	if (args == NULL)
		return;

	for (i = 0; args[i] != NULL; i++)
		free(args[i]);
	free(args);
}

/**
 * execute_command - Execute a command using fork and execve
 * @args: Array of command and arguments
 *
 * Description: This function creates a child process to execute
 * the given command with its arguments.
 * 
 * Return: Exit status of the command
 */
int execute_command(char **args)
{
	pid_t pid;
	int status;

	if (args == NULL || args[0] == NULL)
		return (-1);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		/* Child process */
		if (execve(args[0], args, environ) == -1)
		{
			perror(args[0]);
			exit(127);
		}
	}
	else
	{
		/* Parent process */
		if (wait(&status) == -1)
		{
			perror("wait");
			return (-1);
		}
		
		/* Return the exit status of the child */
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}

	return (0);
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
