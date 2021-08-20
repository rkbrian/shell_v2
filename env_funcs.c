#include "shell.h"

/**
 * dir_num - function to count directories and subdir within the path
 * @env_path: given directory path
 * Return: the count
 */
int dir_num(char *env_path)
{
	int i = 0;
	int count = 0;

	while (env_path[i])
	{
		if (env_path[i] == ':')
			count++;

		i++;
	}
	count++;
	return (count);
}

/**
 * _getenv - function to get environmental variable
 * @name: input string
 * Return: NULL
 */
char *_getenv(const char *name)
{
	int i = 0, j = 0, k = 0, size = 0;
	char *env_var = NULL, *value = NULL;

	while (environ[i])
	{
		if (_strncmp(name, environ[i], _strlen(name)) == 0)
		{
			env_var = _strdup(environ[i]);
			if (env_var == NULL)
				free(env_var);
			while (env_var[j] != '=')
				j++;
			j++;
			size = j;
			while (env_var[size])
				size++;
			value = malloc(sizeof(char) * size);
			if (value == NULL)
			{
				free(value);
				return (NULL);
			}
			while (env_var[j])
			{
				value[k] = env_var[j];
				j++, k++;
			}
			free(env_var);
			return (value);
		}
		i++;
	}
	if (env_var)
		free(env_var);
	if (value)
		free(value);
	return (NULL);
}

/**
 * dir_tokenize - function to tokenize directories
 * @paths: input paths
 * Return: directory tokens
 */
char **dir_tokenize(char *paths)
{
	char **dir_tokens = NULL;
	char *dir = NULL;
	int size = 0;
	int i = 0;

	size = dir_num(paths);
	dir_tokens = malloc(sizeof(char *) * (size + 1));
	if (!dir_tokens)
	{
		free(dir_tokens);
		return (NULL);
	}
	dir = strtok(paths, ":");
	while (dir)
	{
		dir_tokens[i] = _strdup(dir);
		dir = strtok(NULL, ":");
		i++;
	}
	dir_tokens[i] = NULL;
	return (dir_tokens);
}

/**
 * cmd_to_path - function to make new path for input command
 * @path: old path
 * @command: input command
 * Return: new path
 */
char *cmd_to_path(char *path, char *command)
{
	int path_len = 0;
	int command_len = 0;
	char *new_path;

	path_len = _strlen(path);
	command_len = _strlen(command);
	new_path = malloc(sizeof(char) * (path_len + command_len + 2));
	if (!new_path)
	{
		free(new_path);
		return (NULL);
	}
	_strcpy(new_path, path);
	_strcat(new_path, "/");
	_strcat(new_path, command);
	return (new_path);
}
