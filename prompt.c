#include "shell.h"

void prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}
