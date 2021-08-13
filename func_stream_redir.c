#include "shell.h"

/**
 * func_tofile - write or rewrite stream to a file
 * @arglist: linked list of commands
 * @out_token: token on the right of the redirector
 * Return: exit code
 */
int func_tofile(cmd_db *arglist, char *out_token)
{
	pid_t pid;
	struct stat fstat;
	int status, src, fd, excode;

	src = dup(STDOUT_FILENO);
	fd = open(out_token, O_CREAT | O_TRUNC | O_WRONLY);
	dup2(fd, STDOUT_FILENO);

	pid = fork();
	if (pid == -1)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		check_builtins(arglist, arglist->arr);
		if (stat(arglist->token_arr[0], &fstat) == 0)
			execve(arglist->token_arr[0], arglist->token_arr, NULL);
	}
	else
	{
		wait(&status);
		excode = WEXITSTATUS(status);
	}
	close(fd);
	/* fflush(stdout); */
	dup2(src, STDOUT_FILENO);
	close(src);
	return (excode);
}

/**
 * func_addtofile - add stream to a file
 * @arglist: linked list of commands
 * @out_token: token on the right of the redirector
 * Return: exit code
 */
int func_addtofile(cmd_db *arglist, char *out_token)
{
	pid_t pid;
	struct stat fstat;
	int status, src, fd, excode;

	src = dup(STDOUT_FILENO);
	fd = open(out_token, O_CREAT | O_WRONLY | O_APPEND);
	dup2(fd, STDOUT_FILENO);

	pid = fork();
	if (pid == -1)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		check_builtins(arglist, arglist->arr);
		if (stat(arglist->token_arr[0], &fstat) == 0)
			execve(arglist->token_arr[0], arglist->token_arr, NULL);
	}
	else
	{
		wait(&status);
		excode = WEXITSTATUS(status);
	}
	close(fd);
	/* fflush(stdout); */
	dup2(src, STDOUT_FILENO);
	close(src);
	return (excode);
}

/**
 * func_fromfile - acquire all streams from a file
 * @arglist: linked list of commands
 * @out_token: token on the right of the redirector
 * Return: exit code
 */
int func_fromfile(cmd_db *arglist, char *out_token)
{
	pid_t pid;
	struct stat fstat;
	int status, src, fd, excode;

	src = dup(STDIN_FILENO);
	fd = open(out_token, O_RDONLY);
	if (fd == -1)
		return (STDERR_FILENO);
	dup2(fd, STDIN_FILENO);
	pid = fork();
	if (pid == -1)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		check_builtins(arglist, arglist->arr);
		if (stat(arglist->token_arr[0], &fstat) == 0)
			execve(arglist->token_arr[0], arglist->token_arr, NULL);
	}
	else
	{
		wait(&status);
		excode = WEXITSTATUS(status);
	}
	close(fd);
	/* fflush(stdout); */
	dup2(src, STDIN_FILENO);
	close(src);
	return (excode);
}

/* func_heredoc - acquire all streams ends at a given stream */
/* int func_heredoc(cmd_db *arglist, char *out_token) */

/**
 * func_pipeline - function to pipe results of left to right
 * @arglist: linked list of commands
 * @out_token: token on the right of the redirector
 * Return: exit code
 */
/* int func_pipeline(cmd_db *arglist, char *out_token)
{
	int src, fd, excode;
        int status = 0;

	src = dup(STDIN_FILENO);
	}*/
