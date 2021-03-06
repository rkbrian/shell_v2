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
	int i = 0;

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
		else if (current->op_id == 7)
			tmp->excode = 1, sub_exe(current, buffer, argv);
		else if (current->op_id == 5 && current->excode == 0)
			tmp->excode = 1, sub_exe(current, buffer, argv);
		else if (current->op_id == 5)
			tmp->excode = 0, sub_exe(current, buffer, argv);
		else if (current->op_id == 6)
			sub_exe(current, buffer, argv);
		else if (current->op_id == 9)
		{
			tmp = NULL;
			if (prev && prev->op_id < 5 && current->end_id == 0)
				break;
			sub_exe(current, buffer, argv);
		}
		prev = current, current = current->next, i++;
	}
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
	int status, errflag = 0;
	cmd_db *tmp;

	waitgar(current);
	if (current->excode == 0)
	{
		if (check_builtins(current, buffer) != 0)
			return;
		pid = fork();
		if (pid == -1)
			perror("Error\n"), exit(EXIT_FAILURE);
		if (pid == 0)
		{
			if (stat(current->token_arr[0], &fstat) == 0)
				execve(current->token_arr[0], current->token_arr, NULL);
			path_command = check_dir(current->token_arr, argv), tmp = current->next;
			if (path_command != NULL) /* && (_strcmp(current->token_arr[0], "cd") != 0)) */
			{
				execve(path_command, current->token_arr, NULL);
				if (tmp)
					tmp->statue = lstat(path_command, &fstat);
				free(path_command);
			}
			else if (tmp)
				tmp->statue = -1; /* traffic control attempt */
			else
				errflag = 1;
		}
		else
		{
			wait(&status);
			if ((_strcmp(current->token_arr[0], "cd") != 0) && (errflag == 1))
				no_file(current->token_arr[0], argv);
			if (_strcmp(current->token_arr[0], "exit") == 0)
			{
				if (path_command)
					free(path_command);
				_getoutof(current, buffer);
			}
		}
	}
}

/**
 * changedir - function to change directory and env variable
 * @node: input command database
 * @buffer: buffer allocated for input command
 */
void changedir(cmd_db *node, char *buffer)
{
	char *env_str;

	if (node->token_arr[1] == NULL)
	{
		env_str = _getenv("HOME");
		chdir(env_str);
		getcwd(buffer, _strlen(buffer) + _strlen(env_str));
		free(env_str);
	}
	else if (node->token_arr[2] == NULL)
	{
		chdir(node->token_arr[1]);
		getcwd(buffer, _strlen(buffer) + _strlen(node->token_arr[1]));
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
