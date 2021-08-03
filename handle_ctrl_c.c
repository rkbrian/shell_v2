#include "shell.h"

/**
 * handle_ctrl_c - function to handle shell prompt after ctrl + c
 * @signal: void
 */
void handle_ctrl_c(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n$ ", 3);
}
