#include "shell.h"

/**
 * execute - function to execute input command linked list
 * @head: input command linked list
 * @buffer: buffer allocated for input command
 * @argv: argument array
 */
void execute(cmd_db *head, char *buffer, char **argv)
{
	pid_t pid;
	char *path_command = NULL;
	struct stat fstat;
	int status;
	cmd_db *current = NULL, *tmp = NULL;

	current = head;
	pid = fork();
	if (pid == -1)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		while (current)
		{
			check_builtins(current->token_arr, buffer), tmp = current->next;
			current->output_fd = op_process(current, tmp->cmd_head);
			if (stat(current->cmd_head, &fstat) == 0)
			{
				execve(current->cmd_head, current->token_arr, NULL);
				if (_strcmp(current->op, "||") == 0)
					break;
			}
			else if (_strcmp(current->op, "&&") == 0)
				break;
			path_command = check_dir(current->token_arr, argv);
			if (path_command != NULL)
				execve(path_command, current->token_arr, NULL);
			current = current->next; /* (_strcmp(current->op, "||") or ";" == 0) */
		}
	}
	else
	{
		wait(&status);
		if (_strcmp(current->cmd_head, "exit") == 0)
			_getoutof(current->token_arr, buffer);
		free_db(head), free(buffer);
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
 * @out_token: file name in command line
 * Return: output fd
 */
int op_process(cmd_db *arglist, char *out_token)
{
	int output_fd, j;
	op_list opf[] = {
		{">", func_tofile},
		{">>", func_addtofile},
		/*{"<", func_fromfile},*/
		/*{"<<", func_heredoc},*/
		/*{"|", func_pipeline},*/
		{NULL, NULL}
	};
	for (j = 0; opf[j].op != NULL; j++)
	{
		if (_strcmp(opf[j].op, arglist->op) == 0)
		{
			output_fd = opf[j].func(arglist, out_token);
			return (output_fd);
		}
	}
	return (errno);
}
