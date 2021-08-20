#include "shell.h"

/**
 * check_dir - function to check directory path
 * @argv: argument array
 * @command_array: input command
 * Return: NULL
 */
char *check_dir(char **command_array, char **argv)
{
	char **dir_tokens = NULL;
	char *env_path = NULL;
	char *matched = NULL;
	struct stat check;
	int i = 0, j = 0;

	env_path = _getenv("PATH");
	/* printf("check dir envpath: %s\n", env_path); */
	dir_tokens = dir_tokenize(env_path);
	if (env_path)
		free(env_path);
	while (dir_tokens[i])
	{
		dir_tokens[i] = cmd_to_path(dir_tokens[i], command_array[0]);

		if (stat(dir_tokens[i], &check) == 0)
		{
			matched = _strdup(dir_tokens[i]);
			while (dir_tokens[j])
				free(dir_tokens[j]), j++;
			free(dir_tokens);
			return (matched);
		}
		i++;
	}
	(void)argv, j = 0;
	while (dir_tokens[j])
		free(dir_tokens[j]), j++;
	free(dir_tokens);
	/* no_file(command_array[0], argv); */
	return (NULL);
}
