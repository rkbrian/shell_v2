#include "shell.h"

/**
 * func_tofile - write or rewrite stream to a file
 * @arglist: linked list of commands
 */
void func_tofile(cmd_op_list *arglist)
{
	int fd;
        ssize_t wri, i;
        cmd_op_list current = NULL;

        current = arglist;
        if (current == NULL || current->right == NULL)
                return;
        fd = open(current->right, O_CREAT | O_TRUNC | O_WRONLY);
        if (fd == -1)
                return;
        if (current->left == NULL)
                close(fd), return;
        for (i = 0; current->left != '\0'; i++)
        {
        }
        wri = write(fd, current->left, i);
        if (wri == -1)
                return;
        close(fd);
}

/**
 * func_addtofile - add stream to a file
 * @arglist: linked list of commands
 */
void func_addtofile(cmd_op_list *arglist)
{
	int fd;
	ssize_t wri, i;
	cmd_op_list current = NULL;

	current = arglist;
	if (current == NULL || current->right == NULL)
		return;
	fd = open(current->right, O_WRONLY | O_APPEND);
	if (fd == -1)
		return;
	if (current->left == NULL)
		close(fd), return;
	for (i = 0; current->left != '\0'; i++)
	{
	}
	wri = write(fd, current->left, i);
	if (wri == -1)
		return;
	close(fd);
}

/**
 * func_fromfile - acquire all streams from a file
 * @arglist: linked list of commands
 */
void func_fromfile(cmd_op_list *arglist)
{
	ssize_t fd, len, wri;
	char *buffalo;
	cmd_op_list current = NULL;

	current = arglist;
	if (current == NULL || current->right == NULL)
                return;
	fd = open(current->right, ORDONLY);
	len = read(fd, buffalo);
	if (fd == -1)
		return;
	if (_strcmp(current->left, "cat") == 0)
		buffalo = "0\0";
	else
	{
		buffalo = malloc(sizeof(char) * (len + 1));
		if (buffalo == NULL)
			return;
	}






}

/**
 * func_heredoc - acquire all streams ends at a given stream
 * @arglist: linked list of commands
 *
 */
void func_heredoc(cmd_op_list *arglist, char *args)
{



}
