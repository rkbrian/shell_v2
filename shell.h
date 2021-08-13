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
 * struct command_line_database - linked list db, divided by command operators
 * @arr: pointer to the array of each operation, to be tokenized
 * @op: operator pointer
 * @token_arr: pointer to the tokenized array of each operation
 * @end_id: index of the token before operator
 * @op_id: index of the operator in the list
 * input_fd file descriptor for the input for the command
 * output_fd file descriptor for the output for the command
 * @excode: exit code
 * @next: points to the next node
 */
typedef struct command_line_database
{
	char *arr;
	char *op;
	char **token_arr;
	int end_id;
	int op_id;
	/* int input_fd;*/
	/* int output_fd;*/
	int excode;
	struct command_line_database *next;
} cmd_db;

/**
 * struct operators - struct for selecting operations for operator
 * @op: operator pointer
 * @func: function for operation using command line database
 */
typedef struct operators
{
	char *op;
	int (*func)(cmd_db *, char *out_token);
} op_list;

/* puts and putchar */
int _putchar(char c);
void _puts(char *str);
/* tokenizer set */
cmd_db *create_node(char *t_array, int op_id, int starti, int endi);
cmd_db *db_maker(char *str);
int command_count(char *str);
char **tokenize(char *str);
void free_db(cmd_db *headnode);
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
void execute(cmd_db *head, char *buffer, char **argv);
void changedir(char **command_array, char *buffer);
int op_process(cmd_db *arglist, char *out_token);
void sub_exe(cmd_db *current, char *buffer, char **argv);
/* environmental varriable */
char *_getenv(const char *name);
int dir_num(char *env_path);
char **dir_tokenize(char *paths);
char *cmd_to_path(char *path, char *command);
/* directory path checker */
char *check_dir(char **command_array, char **argv);
void no_file(char *cmd, char **argv);
void no_file_sh_v(char *cmd, char **argv);
/* builtins */
int check_builtins(cmd_db *head, char *buffer);
void print_the_env(void);
void _getoutof(cmd_db *head, char *buffer);
void handle_ctrl_c(int signal);
/* stream redirections */
int func_tofile(cmd_db *arglist, char *out_token);
int func_addtofile(cmd_db *arglist, char *out_token);
int func_fromfile(cmd_db *arglist, char *out_token);
/* int func_heredoc(cmd_db *arglist, char *out_token); */
/* int func_pipeline(cmd_db *arglist, char *out_token); */
/* command operators */
/* int func_separate(cmd_db *arglist); */
/* int func_and(cmd_db *arglist); */
/* int func_or(cmd_db *arglist); */

#endif
