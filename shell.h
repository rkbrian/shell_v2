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

typedef struct commands_w_op
{
	char **left_cmd;
	char *op;
	int position = 0;
	char **right_cmd;
	int (*f)(struct commands_w_op *);
	struct commands_w_op *next;
} cmd_op_list;

typedef struct operators
{
	char *op;
	int (*func)(cmd_op_list *);
} op_list;

/* puts and putchar */
int _putchar(char c);
void _puts(char *str);
/* tokenizer set */
void op_selector(cmd_op_list *arglist, char *args);
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
void func_tofile(cmd_op_list *arglist);
void func_addtofile(cmd_op_list *arglist);
void func_fromfile(cmd_op_list *arglist);
void func_heredoc(cmd_op_list *arglist);
/* command operators */
void func_pipeline(cmd_op_list *arglist);
void func_separate(cmd_op_list *arglist);
void func_and(cmd_op_list *arglist);
void func_or(cmd_op_list *arglist);

#endif
