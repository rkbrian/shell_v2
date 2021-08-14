#include "shell.h"

/**
 * execute - function to execute input command linked list
 * @head: input command linked list
 * @buffer: buffer allocated for input command
 * @argv: argument array
 */
void execute(cmd_db *head, char *buffer, char **argv)
{
	cmd_db *current = NULL, *tmp = NULL, *prev = NULL;

	current = head;
	while (current)
	{
		tmp = current->next;
		if (current->op_id < 5)
		{
			current->excode = op_process(current, tmp->token_arr[0]);
			tmp->excode = current->excode;
		}
		else if (current->op_id == 7 && current->excode == 0)
			tmp->excode = 0, sub_exe(current, buffer, argv);
		else if (current->op_id == 7 && current->excode != 0)
			tmp->excode = 1, sub_exe(current, buffer, argv);
		else if (current->op_id == 5 && current->excode == 0)
			tmp->excode = 1, sub_exe(current, buffer, argv);
		else if (current->op_id == 5 && current->excode != 0)
			tmp->excode = 0, sub_exe(current, buffer, argv);
		else if (current->op_id == 9)
		{
			tmp = NULL;
			if (prev && prev->op_id < 5 && current->end_id == 0)
				break;
			sub_exe(current, buffer, argv);
		}
		prev = current, current = current->next;
	}
	/* free_db(head); */
	free(buffer);
}

/**
 * sub_exe- adjust database and then execute
 * @current: current node
 * @buffer: buffer allocated for input command
 * @argv: argument array
 */
void sub_exe(cmd_db *current, char *buffer, char **argv)
{
	pid_t pid;
	char *path_command = NULL;
	struct stat fstat;
	int status;
	cmd_db *tmp;

	pid = fork();
	if (pid == -1)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		check_builtins(current, buffer);
		if (stat(current->token_arr[0], &fstat) == 0)
			execve(current->token_arr[0], current->token_arr, NULL);
		path_command = check_dir(current->token_arr, argv), tmp = current->next;
		if (path_command != NULL)
		{
			execve(path_command, current->token_arr, NULL);
			if (tmp)
				tmp->statue = lstat((const char *)path_command, fstat);
			free(path_command);
		}
		else if (tmp)
			tmp->statue = -1;
	}
	else
	{
		wait(&status);
		if (_strcmp(current->token_arr[0], "exit") == 0)
			_getoutof(current, buffer);
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
 * Return: exit code
 */
int op_process(cmd_db *arglist, char *out_token)
{
	int excode, j;
	op_list opf[] = {
		{">", func_tofile},
		{">>", func_addtofile},
		{"<", func_fromfile},
		/*{"<<", func_heredoc},*/
		/*{"|", func_pipeline},*/
		{NULL, NULL}
	};

	for (j = 0; opf[j].op != NULL; j++)
	{
		if (_strcmp(opf[j].op, arglist->op) == 0)
		{
			excode = opf[j].func(arglist, out_token);
			return (excode);
		}
	}
	return (errno);
}
