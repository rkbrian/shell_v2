#include "shell.h"

/**
 * create_node - function to create new node of command line database
 * @t_array: token array
 * @op: operator token
 * @
 * Return: command line database node
 */
cmd_db *create_node(char **t_array, char *op)
{
	cmd_db *node = NULL;
	int i = 0;

	node = malloc(sizeof(cmd_db));
	if (node == NULL)
		return (NULL);
	while (t_array[i])
		node->token_arr[i] = t_array[i], i++;
	node->cmd_head = t_array[0];
	if (op)
		node->op = op;
	else
		node->op = NULL;
	node->next = NULL;
	return (node);
}

/**
 * tokenize - function to tokenize input commands separated by spaces
 * @str: input commands
 * Return: array of tokenized commands
 */
char **tokenize(char *str)
{
	char *token = NULL, **token_col = NULL, *token_head = NULL;
	char *proc_op[] = {">", ">>", "<", "<<", "|", ";", "&&", "||"}
	int size = 0, i = 0, j = 0, headflag = 0;
	cmd_db *current = NULL, *head = NULL;

	str[_strlen(str) - 1] = '\0', size = command_count(str);
	if (size == 0)
		return (NULL);
	token_col = malloc((sizeof(char *)) * (size + 1));
	if (!token_col)
		return (NULL);
	while ((token = strtok(str, " ")))
	{
		for (; proc_op[j] != NULL; j++)
		{
			if (_strcmp(token, proc_op[j]) == 0)
			{
				token_col[i] = NULL, current = create_node(token_col, token);
				if (headflag == 0)
					head = current, headflag = 1;
				current = current->next, token_col = NULL, i = 0;
				break;
			}
		}
		token_col[i] = malloc(_strlen(token) + 1);
		if (token_col[i] == NULL)
		{
			for (i--; i >= 0; i--)
				free(token_col[i]);
			free(token_col);
			return (NULL);
		}
		_strncpy(token_col[i], token, _strlen(token) + 1);
		token = strtok(NULL, " "), i++;
	}
	token_col[i] = NULL, current = create_node(token_col, NULL);
	current->next == NULL;
	return (head);
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
		headnode->cmd_head = NULL;
		for (i = 0; headnode->token_arr[i] != NULL; i++)
			free(headnode->token_arr[i]);
		tmp_node = headnode->next;
		free(headnode);
		headnode = tmp_node;
	}
}
