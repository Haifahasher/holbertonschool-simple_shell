#include "shell.h"
/**
 * prompt - Displays the shell prompt
 *
 * Return: Nothing
 */
void prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}
