#include "shell.h"

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

/**
 * new_node - function to create new node of command line database
 * @token_arr: token array
 * @token: the first token of the process
 * @op_flag: operator flag, 1 for existance, 0 for none
 * Return: command line database node
 */
cmd_db *new_node(char **token_col, char *token, int op_flag)
{
	cmd_db *newnode = NULL;

	new_node = malloc(

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


	return (current);
}

/**
 * command_count - function to count commands
 * @str: input commands
 * Return: count of commands
 */
int command_count(char *str)
{
	int count = 0, boool = 0, i = 0;
	int db_quote_flag = 1, sg_quote_flag = 1;

	while (str[i])
	{
		if (str[i] == ' ')
		{
			/*if (str[i + 1] == '\"')
			{
				db_quote_flag = db_quote_flag * (-1);
				if (db_quote_flag > 0)
					count++, boool = 1;
			}
			else if (str[i + 1] == '\'')
			{
				sg_quote_flag = sg_quote_flag * (-1);
				if (sg_quote_flag > 0)
					count++, boool = 1;
			}
			else */
			boool = 0;
		}
		else if (boool == 0)
			count++, boool = 1;
		i++;
	}
	return (count);
}

/**
 * tokenize - function to tokenize input commands separated by spaces
 * @str: input commands
 * Return: array of tokenized commands
 */
char **tokenize(char *str)
{
	char *token = NULL, **token_col = NULL;
	int size = 0, i = 0, position = 0;
	cmd_db *arglist = NULL;

	str[_strlen(str) - 1] = '\0';
	size = command_count(str);
	if (size == 0)
		return (NULL);
	token_col = malloc((sizeof(char *)) * (size + 1));
	if (!token_col)
		return (NULL);
	arglist = malloc(sizeof(cmd_op_list));
	if (arglist == NULL)
		return (NULL);
	while ((token = strtok(str, " "))
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
		token = strtok(NULL, " "), i++;
	}
	token_col[i] = NULL;
	return (token_col);
}

/**
 * free_token - function to free malloc of ptr to tokenized command array
 * @tokcmd: tokenized command array
 */
void free_token(char **tokcmd)
{
	int i;

	for (i = 0; tokcmd[i] != NULL; i++)
	{
		free(tokcmd[i]);
	}
	if (tokcmd != NULL)
	{
		free(tokcmd);
	}
}
