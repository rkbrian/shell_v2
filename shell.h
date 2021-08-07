#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

extern char **environ;

/**
 * cmd_db - linked list database for command lines, divided by command operators
 * @token_arr: pointer to the token array of each operation
 * @cmd_head: pointer to the starting token of each operation
 * @op: operator pointer
 * @input_fd: file descriptor for the input for the command
 * @output_fd: file descriptor for the output for the command
 */
typedef struct command_line_database
{
	char **token_arr;
	char *cmd_head;
	char *op;
	int input_fd;
	int output_fd;
	struct command_line_database *next;
} cmd_db;

/**
 * op_list - struct for selecting operations for operator
 * @op: operator pointer
 * @func: function for operation using command line database
 */
typedef struct operators
{
	char *op;
	int (*func)(cmd_db *);
} op_list;

/* puts and putchar */
int _putchar(char c);
void _puts(char *str);
/* tokenizer set */
void op_selector(cmd_op_list *arglist, char *args);
cmd_db *new_node(char *token, int op_flag);
int command_count(char *str);
char **tokenize(char *str);
void free_token(char **tokcmd);
/* helper function set 1 */
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, const char *src);
int _strlen(const char *s);
char *_strcat(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);
/* helper function set 2 */
void *_realloc(void *ptr, unsigned int new_size);
int _strncmp(const char *s1, const char *s2, int len);
char *_strdup(const char *str);
/* unused: void exit_shell(char **command_array, char *buffer); */
/* execute function */
void execute(char **command_array, char *buffer, char **argv);
void changedir(char **command_array, char *buffer);

/* environmental varriable */
char *_getenv(const char *name);
int dir_num(char *env_path);
char **dir_tokenize(char *paths);
char *cmd_to_path(char *path, char *command);
/* directory path checker */
char *check_dir(char **command_array, char **argv);
void no_file(char *cmd, char **argv);
void no_file_sh_v(char *cmd, char **argv);
/* handle ctrl-c */
void handle_ctrl_c(int signal);
/* builtins */
int check_builtins(char **command_array, char *buffer);
void print_the_env(void);
void _getoutof(char **command_array, char *buffer);
/* stream redirections */
int func_tofile(cmd_db *arglist);
int func_addtofile(cmd_db *arglist);
int func_fromfile(cmd_db *arglist);
int func_heredoc(cmd_db *arglist);
/* command operators */
int func_pipeline(cmd_db *arglist);
int func_separate(cmd_db *arglist);
int func_and(cmd_db *arglist);
int func_or(cmd_db *arglist);

#endif
