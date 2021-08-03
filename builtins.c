#include "shell.h"

/**
 * check_builtins - built-in functions for special commands
 * @command_array: input command
 * @buffer: buffer allocated for input command
 * Return: 0
 */
int check_builtins(char **command_array, char *buffer)
{
	char *builtins[] = { "exit", "env", "cd", NULL };
	int i = 0;

	while (builtins[i])
	{
		if (_strcmp(command_array[0], builtins[i]) == 0)
		{
			switch (i)
			{
			case 0:
				_getoutof(command_array, buffer);
				break;
			case 1:
				print_the_env();
				return (1);
			case 2:
				changedir(command_array, buffer);
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
 * @command_array: command array
 * @buffer: input buffer
 */
void _getoutof(char **command_array, char *buffer)
{
	free_token(command_array);
	free(buffer);
	exit(EXIT_SUCCESS);
}
