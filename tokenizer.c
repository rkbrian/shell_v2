#include "shell.h"

/**
 * create_node - function to create new node of command line database
 * @t_array: token array
 * @op_id: operator token index
 * @starti: starting point of array
 * @endi: end point of array
 * Return: command line database node
 */
cmd_db *create_node(char *t_array, int op_id, int starti, int endi)
{
	cmd_db *node = NULL;
	int i = 0, j = 0;
	char *proc_op[] = {">", ">>", "<", "<<", "|", ";", "&&", "||"};

	node = malloc(sizeof(cmd_db));
	if (node == NULL)
		return (NULL);
	node->token_arr = malloc(sizeof(char) * (endi - starti + 1));
	if (node->token_arr == NULL)
		return (NULL);
	for (i = 0, i < endi - starti; i++)
		node->token_arr[i] = t_array[starti + i];
	node->token_arr[i] = '\0';
	for (; j < 8; j++)
	{
		if (op_id == j)
			node->op = proc_op[j];
		else
			node->op = NULL;
	}
	node->next = NULL;
	return (node);
}

/**
 * db_maker - find command operators and make command databasex
 * @str: command string
 */
cmd_db *db_maker(char *str)
{
	int long_len, k = 0, oid, stri = 0, headflag = 0;
	cmd_db *cur = NULL, *head = NULL;

	long_len = _strlen(str);
	while (k < long_len)
	{
		if (str[k] == '>')
		{
			if (str[k + 1] == '>')
				oid = 1, cur = create_node(str, oid, stri, k), stri = k + 2, headflag++;
			else
				oid = 0, cur = create_node(str, oid, stri, k), stri = k + 1, headflag++;
		}
		else if (str[k] == '<')
		{
			if (str[k + 1] == '<')
				oid = 3, cur = create_node(str, oid, stri, k), stri = k + 2, headflag++;
			else
				oid = 2, cur = create_node(str, oid, stri, k), stri = k + 1, headflag++;
		}
		else if (str[k] == '|')
		{
			if (str[k + 1] == '|')
				oid = 7, cur = create_node(str, oid, stri, k), stri = k + 2, headflag++;
			else
				oid = 4, cur = create_node(str, oid, stri, k), stri = k + 1, headflag++;
		}
		else if (str[k] == ';')
			oid = 5, cur = create_node(str, oid, stri, k), stri = k + 1, headflag++;
		else if (str[k] == '&' && str[k + 1] == '&')
			oid = 6, cur = create_node(str, oid, stri, k), stri = k + 2, headflag++;
		if (headflag == 1)
			head = cur, cur = cur->next, headflag = 2;
		else if (headflag > 2)
			cur = cur->next, headflag = 2;
		k++;
	}
	return (head);
}

/**
 * tokenize - function to tokenize input commands separated by spaces
 * @str: input commands
 * Return: array of tokenized commands
 */
char **tokenize(char *str)
{
	char *token = NULL;
	char **token_col = NULL;
	int size = 0, i = 0;

	str[_strlen(str) - 1] = '\0';
	size = command_count(str);
	if (size == 0)
		return (NULL);
	token_col = malloc((sizeof(char *)) * (size + 1));
	if (!token_col)
	{
		free(token_col);
		return (NULL);
	}
	token = strtok(str, " ");
	while (token)
	{
		token_col[i] = malloc(_strlen(token) + 1);
		if (token_col[i] == NULL)
		{
			for (i--; i >= 0; i--)
				free(token_col[i]);
			free(token_col);
			return (NULL);
		}
		_strncpy(token_col[i], token, _strlen(token) + 1);
		token = strtok(NULL, " ");
		i++;
	}
	token_col[i] = NULL;
	return (token_col);
}

/**
 * command_count - function to count commands
 * @str: input commands
 * Return: count of commands
 */
int command_count(char *str)
{
	int count = 0, boool = 0, i = 0;

	while (str[i])
	{
		if (str[i] == ' ')
			boool = 0;
		else if (boool == 0)
			count++, boool = 1;
		i++;
	}
	return (count);
}

/**
 * free_db - function to free malloc of ptr to tokenized command array
 * @headnode: tokenized command struct
 */
void free_db(cmd_db *headnode)
{
	cmd_db *tmp_node;
	int i;

	if (headnode == NULL)
		return;
	while (headnode)
	{
		free(headnode->token_arr);
		headnode->op = NULL;
		tmp_node = headnode->next;
		free(headnode);
		headnode = tmp_node;
	}
}
