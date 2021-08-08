#include "shell.h"

/**
 * execute - function to execute input command
 * @head: input command
 * @buffer: buffer allocated for input command
 * @argv: argument array
 */
void execute(cmd_db *head, char *buffer, char **argv)
{
	pid_t pid;
	char *path_command = NULL;
	struct stat fstat;
	int status;
	cmd_db *current;

	pid = fork();
	if (pid == -1)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		check_builtins(head->token_arr, buffer);
		if (stat(head->token_arr[0], &fstat) == 0)
			execve(head->token_arr[0], head->token_arr, NULL);

		path_command = check_dir(head->token_arr, argv);
		if (path_command != NULL)
			execve(path_command, head->token_arr, NULL);
	}
	else
	{
		wait(&status);
		if (_strcmp(head->token_arr[0], "exit") == 0)
			_getoutof(head->token_arr, buffer);
		free_db(head);
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

/**
 * op_process - function to check if it is an operator for process
 * @arglist: linked list of commands
 * Return: 1 for matched op, 0 for no
 */
int *op_process(cmd_db *arglist)
{
        int j;
        op_list opf[] = {
                {">", func_tofile},
                {">>", func_addtofile},
                {"<", func_fromfile},
                {"<<", func_heredoc},
                {"|", func_pipeline},
                {";", func_separate},
                {"&&", func_and},
                {"||", func_or},
                {NULL, NULL}
        };
        for (j = 0; opf[j].op != NULL, j++)
        {
                if (_strcmp(opf[j].op, arglist->op) == 0)
                {
                        opf[j].func(arglist);
                        return (1);
                }
        }
        return (0);
}
