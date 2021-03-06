#include "shell.h"

/**
 * _realloc - function reallocates a memory
 * @ptr: a pointer to the memory previously allocated
 * @new_size: new size in bytes of the allocated space for ptr
 * Return: pointer or null
 */
void *_realloc(void *ptr, unsigned int new_size)
{
	void *newsp;

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	newsp = malloc(new_size);
	if (newsp == NULL)
	{
		return (NULL);
	}
	free(ptr);
	return (newsp);
}

/**
 * _strncmp - Compares two strings within a cerrtain length.
 * @s1: String one
 * @s2: String two
 * @len: section length of the strings to be compared from start
 * Return: Difference
 */
int _strncmp(const char *s1, const char *s2, int len)
{
	int i, ret;
	char *sa, *sb;

	sa = malloc(sizeof(char) * (len + 1));
	sb = malloc(sizeof(char) * (len + 1));
	for (i = 0; s1[i] != '\0' && s2[i] != '\0' && i < len; i++)
	{
		sa[i] = s1[i];
		sb[i] = s2[i];
	}
	while ((*sa != '\0' && *sb != '\0') && *sa == *sb)
	{
		sa++;
		sb++;
	}
	ret = *sa - *sb;
	if (*sa == *sb)
	{
		free(sa);
		free(sb);
		return (0);
	}
	if (sa)
		free(sa);
	if (sb)
		free(sb);
	return (ret);
}

/**
 * _strdup - function to duplicate a string.
 * @str: input string
 * Return: pointer to the string
 */
char *_strdup(const char *str)
{
	int len = _strlen(str) + 1;
	char *new = malloc(sizeof(char) * len);

	if (new == NULL)
		return (NULL);

	return (_strcpy(new, str));
}

/**
 * exit_shell - function to exit shell in both child and parent processes
 * @command_array: command array
 * @buffer: input buffer
 */
void exit_shell(char **command_array, char *buffer)
{
	int i;

	for (i = 0; command_array[i] != NULL; i++)
		free(command_array[i]);
	free(buffer);
}

/**
 * waitgar - wait for gargoyle status
 * @node: node with gargoyle status
 */
void waitgar(cmd_db *node)
{
	int gargoyle;

	gargoyle = node->statue;
	if (gargoyle == 0)
		wait(&gargoyle);
}
