#include "shell.h"

/**
 * func_tofile - write or rewrite stream to a file
 * @arglist: linked list of commands
 * Return: -1 for errno, 1 for stdout
 */
int func_tofile(cmd_db *arglist, char *out_token)
{
	int fd;
	ssize_t wri, i, j;
	cmd_db *current = NULL;

	current = arglist;
	if (current == NULL || out_token == NULL)
		return (-1);
	fd = open(out_token, O_CREAT | O_TRUNC | O_WRONLY);
	if (fd == -1)
		return (-1);
	if (current->token_arr == NULL)
	{
		close(fd);
		return (1);
	}
	for (j = 0; current->token_arr[j] != NULL; j++)
	{
	}
	for (i = 0; current->token_arr[j][i] != '\0'; i++)
	{
	}
	wri = write(fd, current->token_arr[j], i);
	if (wri == -1)
		return (-1);
	close(fd);
	return (1);
}

/**
 * func_addtofile - add stream to a file
 * @arglist: linked list of commands
 * Return: -1 for errno, 1 for stdout
 */
int func_addtofile(cmd_db *arglist, char *out_token)
{
	int fd;
	ssize_t wri, i, j;
	cmd_db *current = NULL;

	current = arglist;
	if (current == NULL || out_token == NULL)
		return (-1);
	fd = open(out_token, O_WRONLY | O_APPEND);
	if (fd == -1)
		return (-1);
	if (current->token_arr == NULL)
	{
		close(fd);
		return (1);
	}
	for (j = 0; current->token_arr[j] != NULL; j++)
	{
	}
	for (i = 0; current->token_arr[j][i] != '\0'; i++)
	{
	}
	wri = write(fd, current->token_arr[j], i);
	if (wri == -1)
		return (-1);
	close(fd);
	return (1);
}

/**
 * func_fromfile - acquire all streams from a file
 * @arglist: linked list of commands
 * Return: 0 or 1
 */
int func_fromfile(cmd_db *arglist, char *out_token)
{
	ssize_t fd, len, wri;
	char *buffalo;
	cmd_db *current = NULL;
	int j;

	current = arglist;
	if (current == NULL || out_token == NULL)
		return (0);
	fd = open(out_token, O_RDONLY);
	for (j = 0; current->token_arr[j] != NULL; j++)
	{
	}
	buffalo = malloc(sizeof(char) * 1024);
	if (buffalo == NULL)
		return (0);
	if (fd == -1)
	{
		free(buffalo);
		return (0);
	}
	len = read(fd, buffalo, 1023);
	if (len == -1)
	{
		free(buffalo), close(fd);
		return (0);
	}
	wri = write(STDOUT_FILENO, buffalo, len);
	if (wri == -1)
	{
		free(buffalo), close(fd);
		return (0);
	}
	free(buffalo), close(fd);
	return (len);
}

/**
 * func_heredoc - acquire all streams ends at a given stream
 * @arglist: linked list of commands
 * Return: 0 or 1
 */
/* int func_heredoc(cmd_db *arglist, char *out_token) */

/**
 * func_pipeline - function to pipe results of left to right
 * @arglist: linked list of commands

 * Return: 0 or 1
 */
/* int func_pipeline(cmd_db *arglist, char *out_token) */
