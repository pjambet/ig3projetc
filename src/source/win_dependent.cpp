/********************************************/
/* Author: Razvan Dinu                      */
/* Project: Projet C IG3                    */
/* Date: 13.04.2010                         */
/********************************************/
#include <stdio.h>
#include "../headers/win_dependent.h"

// Executes a command and waits for it to finish.
// The command should work on the shell (executable should be in PATH).
int exec_and_wait(char* command)
{
	STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    // Start the child process.
    if( !CreateProcessA( NULL,   // No module name (use command line)
        command,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    )
    {
        printf( "CreateProcess failed (%d).\n", (int) GetLastError() );
        return 1;
    }

    // Wait until child process exits.
    if (WaitForSingleObject( pi.hProcess, INFINITE ))
	{
		printf("There was an error waiting for the process.\n");
		return 1;
	}

    // Close process and thread handles.
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );

	return 0;
}
