#include "shell.h"

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
	char *token = NULL;
	char **token_col = NULL;
	int size = 0;
	int i = 0;

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