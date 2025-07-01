#include "shell.h"

/**
 * tokenize - Split a line into tokens (command and arguments)
 * @line: The input line to tokenize
 *
 * Description: Splits the input line into tokens using space as delimiter.
 * Handles multiple spaces and creates an array of strings.
 *
 * Return: Array of tokens, or NULL on failure
 */
char **tokenize(char *line)
{
	char **tokens;
	char *token;
	char *line_copy; /* Copy of the line to handle strtok */
	int position = 0;
	int bufsize = MAX_ARGS;

	if (line == NULL)
		return (NULL);

	/* Create a copy of the line since strtok modifies the original string */
	line_copy = _strdup(line);
	if (line_copy == NULL)
		return (NULL);

	/* Allocate memory for tokens array */
	tokens = malloc(bufsize * sizeof(char *));
	if (tokens == NULL)
	{
		perror("malloc");
		free(line_copy);
		return (NULL);
	}

	/* Get the first token */
	token = strtok(line_copy, DELIM);
	while (token != NULL)
	{
		/* Store a copy of the token */
		tokens[position] = _strdup(token);
		if (tokens[position] == NULL)
		{
			/* Free previously allocated memory on failure */
			int i;
			for (i = 0; i < position; i++)
				free(tokens[i]);
			free(tokens);
			free(line_copy);
			return (NULL);
		}
		position++;

		/* Check if we need to reallocate */
		if (position >= bufsize)
		{
			bufsize += MAX_ARGS;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (tokens == NULL)
			{
				perror("realloc");
				free(line_copy);
				return (NULL);
			}
		}

		/* Get next token */
		token = strtok(NULL, DELIM);
	}

	/* Null-terminate the array */
	tokens[position] = NULL;
	free(line_copy); /* Free the temporary copy */
	return (tokens);
}

/**
 * trim_spaces - Remove leading and trailing spaces from a string
 * @str: String to trim
 *
 * Description: Removes spaces, tabs, and newlines from the beginning
 * and end of the string.
 *
 * Return: Pointer to the trimmed string
 */
char *trim_spaces(char *str)
{
	char *end;

	if (str == NULL)
		return (NULL);

	/* Trim leading spaces */
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r')
		str++;

	/* If string is all spaces */
	if (*str == '\0')
		return (str);

	/* Trim trailing spaces */
	end = str + _strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r'))
		end--;

	/* Null terminate */
	end[1] = '\0';

	return (str);
}

/**
 * _strcmp - Compare two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: 0 if strings are equal, negative if s1 < s2, positive if s1 > s2
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	if (s1 == NULL || s2 == NULL)
		return (-1);

	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

/**
 * _strdup - Duplicate a string
 * @str: String to duplicate
 *
 * Return: Pointer to duplicated string, or NULL on failure
 */
char *_strdup(char *str)
{
	char *dup;
	int i, len = 0;

	if (str == NULL)
		return (NULL);

	/* Calculate string length */
	while (str[len])
		len++;

	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);

	/* Copy string */
	for (i = 0; i < len; i++)
		dup[i] = str[i];
	dup[i] = '\0';

	return (dup);
}

/**
 * _strlen - Get length of a string
 * @s: String to measure
 *
 * Return: Length of string
 */
int _strlen(char *s)
{
	int len = 0;

	if (s == NULL)
		return (0);

	while (s[len])
		len++;

	return (len);
}
