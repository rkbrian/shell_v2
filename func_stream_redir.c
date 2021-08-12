#include "shell.h"

/**
 * func_tofile - write or rewrite stream to a file
 * @arglist: linked list of commands
 * @out_token: token on the right of the redirector
 * Return: exit code
 */
int func_tofile(cmd_db *arglist, char *out_token)
{
	int src, fd, excode;
	int status = 0;

	src = dup(STDOUT_FILENO);
	fd = open(out_token, O_CREAT | O_TRUNC | O_WRONLY);
	if (!fork())
	{
		execve(arglist->token_arr[0], arglist->token_arr, NULL);
		perror(NULL);
		exit(2);
	}
	wait(&status);
	excode = WEXITSTATUS(status);
	close(fd);

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
	int src, fd, excode;
	int status = 0;

	src = dup(STDOUT_FILENO);
	fd = open(out_token, O_CREAT | O_WRONLY | O_APPEND);
	if (!fork())
	{
		execve(arglist->token_arr[0], arglist->token_arr, NULL);
		perror(NULL);
		exit(2);
	}
	wait(&status);
	excode = WEXITSTATUS(status);
	close(fd);

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
	int src, fd, excode;
	int status = 0;

	src = dup(STDIN_FILENO);
	fd = open(out_token, O_RDONLY);
	if (fd == -1)
		return (2);
	dup2(fd, STDIN_FILENO);
	if (!fork())
	{
		execve(arglist->token_arr[0], arglist->token_arr, NULL);
		perror(NULL);
		exit(2);
	}
	wait(&status);
	excode = WEXITSTATUS(status);
	close(fd);

	dup2(src, STDIN_FILENO);
	close(src);
	return (excode);
}

/**
 * func_heredoc - acquire all streams ends at a given stream
 * @arglist: linked list of commands
 * @out_token: token on the right of the redirector
 * Return: exit code
 */
/* int func_heredoc(cmd_db *arglist, char *out_token) */

/**
 * func_pip - function to pipe results of left to right
 * @arglist: linked list of commands
 * @out_token: token on the right of the redirector
 * Return: exit code
 */
/* int func_pip(cmd_db *arglist, char *out_token) */
