#include "shell.h"

/**
 * search_path_dirs - Searches PATH directories for a command
 * @path: PATH string
 * @command: Command to find
 *
 * Return: malloc'd full path if found, NULL otherwise
 */
char *search_path_dirs(char *path, char *command)
{
	char *path_cpy, *dir, *full_path;
	struct stat st;
	int len;

	path_cpy = strdup(path);
	dir = strtok(path_cpy, ":");
	while (dir)
	{
		len = strlen(dir) + strlen(command) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_cpy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, command);
		if (stat(full_path, &st) == 0)
		{
			free(path_cpy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_cpy);
	return (NULL);
}

/**
 * find_path - Finds the full path of a command
 * @command: The command to find
 *
 * Return: Full path (malloc'd) or command if found as is
 */
char *find_path(char *command)
{
	char *path = NULL;
	struct stat st;
	int i = 0;

	if (strchr(command, '/'))
	{
		if (stat(command, &st) == 0)
			return (command);
		else
			return (NULL);
	}

	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5;
			break;
		}
		i++;
	}
	if (!path)
		return (NULL);

	return (search_path_dirs(path, command));
}
