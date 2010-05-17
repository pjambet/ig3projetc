/********************************************/
/* Author: Razvan Dinu                      */
/* Project: Projet C IG3                    */
/* Date: 13.04.2010                         */
/********************************************/
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../headers/unix_dependent.h"

#define SHELL "/bin/sh"

// Executes a command and waits for it to finish.
// The command should work on the shell (executable should be in PATH).
int exec_and_wait(char* command)
{
	int status;
	pid_t pid;

	pid = fork ();
	if (pid == 0)
	{
	  /* This is the child process.  Execute the shell command. */
	  execl (SHELL, SHELL, "-c", command, NULL);
	}
	else if (pid < 0)
	{
		perror("Fork failed.");
		/* The fork failed.  Report failure.  */
		status = -1;
	}
	else
	/* This is the parent process.  Wait for the child to complete.  */
	if (waitpid (pid, &status, 0) != pid)
	  status = -1;

	return 0;
}
