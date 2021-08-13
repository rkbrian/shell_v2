#include "shell.h"

/**
 * check_builtins - built-in functions for special commands
 * @head: input command database
 * @buffer: buffer allocated for input command
 * Return: 0
 */
int check_builtins(cmd_db *head, char *buffer)
{
	char *builtins[] = { "exit", "env", "cd", NULL };
	int i = 0;

	while (builtins[i])
	{
		if (_strcmp(head->token_arr[0], builtins[i]) == 0)
		{
			switch (i)
			{
			case 0:
				_getoutof(head, buffer);
				break;
			case 1:
				print_the_env();
				return (1);
			case 2:
				changedir(head->token_arr, buffer);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

/**
 * print_the_env - function to print environmental variable
 */
void print_the_env(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		_puts(environ[i]);
		_putchar('\n');
	}
}

/**
 * _getoutof - function to exit shell in both child and parent processes
 * @head: input command database
 * @buffer: input buffer
 */
void _getoutof(cmd_db *head, char *buffer)
{
	free(buffer);
	free_db(head);
	exit(EXIT_SUCCESS);
}

/**
 * handle_ctrl_c - function to handle shell prompt after ctrl + c
 * @signal: void
 */
void handle_ctrl_c(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n$ ", 3);
}
