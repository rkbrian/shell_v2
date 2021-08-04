#include "shell.h"

/**
 * op_selector - operator selector
 * @arglist: linked list of commands
 * @args: operator string from commands
 */
void op_selector(cmd_op_list *arglist, char *args)
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
		if (_strcmp(opf[j].op, args) == 0)
			opf[j].func(arglist, args);
	}
}

/**
 * command_count - function to count commands
 * @str: input commands
 * Return: count of commands
 */

int command_count(char *str)
{
	int count = 0;
	int i = 0;
	int boool = 0;

	while (str[i])
	{
		if (str[i] == ' ')
			boool = 0;
		else if (boool == 0)
		{
			count++;
			boool = 1;
		}
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
	int size = 0, i = 0;
	cmd_op_list *arglist;

	str[_strlen(str) - 1] = '\0';
	size = command_count(str);
	if (size == 0)
		return (NULL);
	token_col = malloc((sizeof(char *)) * (size + 1));
	if (!token_col)
		return (NULL);
	while ((token = strtok(str, " "))
	{
		op_selector(token);

	}
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
