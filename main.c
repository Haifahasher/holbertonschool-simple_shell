c
CopyEdit
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define PROMPT "($) "

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    int status;

    while (1)
    {
        write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
        nread = getline(&line, &len, stdin);
        if (nread == -1)  /* EOF */
        {
            free(line);
            exit(0);
        }

        /* strip newline */
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        pid = fork();
        if (pid == 0)    /* child */
        {
            char *args[] = { line, NULL };
            execve(args[0], args, environ);
            perror("hsh");  /* execve failed */
            exit(1);
        }
        else if (pid > 0)  /* parent */
            wait(&status);
        else
            perror("hsh");
    }

    return (0);
}
