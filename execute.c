#include "shell.h"

/**
 * execute - function to execute input command
 * @command_array: input command
 * @buffer: buffer allocated for input command
 * @argv: argument array
 */

void execute(char **command_array, char *buffer, char **argv)
{
	pid_t pid;
	char *path_command = NULL;
	struct stat fstat;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		check_builtins(command_array, buffer);
		if (stat(command_array[0], &fstat) == 0)
			execve(command_array[0], command_array, NULL);

		path_command = check_dir(command_array, argv);
		if (path_command != NULL)
			execve(path_command, command_array, NULL);
	}
	else
	{
		wait(&status);
		if (_strcmp(command_array[0], "exit") == 0)
			_getoutof(command_array, buffer);
		free_token(command_array);
		free(buffer);
	}
}

/**
 * changedir - function to change directory and env variable
 * @command_array: input command
 * @buffer: buffer allocated for input command
 */
void changedir(char **command_array, char *buffer)
{
	if (!command_array[1])
	{
		chdir("HOME");
		getcwd(buffer, _strlen(buffer));
	}
	else if (!command_array[2])
	{
		chdir(command_array[1]);
		getcwd(buffer, _strlen(buffer));
	}
	else
		perror("getcwd");
}