/********************************************/
/* Author: Razvan Dinu                      */
/* Project: Projet C IG3                    */
/* Date: 13.04.2010                         */
/********************************************/
#ifndef __OS_DEPENDENT__
#define __OS_DEPENDENT__
#include <windows.h>

// Executes a command and waits for it to finish.
// The command should work on the shell (executable should be in PATH).
int exec_and_wait(char* command);

#endif
