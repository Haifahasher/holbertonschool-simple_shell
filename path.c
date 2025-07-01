#include "shell.h"

/**
 * find_path - Finds the full path of a command
 * @command: The command to find
 * Return: Full path (malloc'd) or command if found as is
 */
char *find_path(char *command)
{
	char *path, *path_cpy, *dir, *full_path;
	struct stat st;
	int len;

	if (stat(command, &st) == 0)
		return (command);
	path = getenv("PATH");
	if (!path)
		return (NULL);
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
