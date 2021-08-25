# Shell V2

## Description

This is a simple shell created for a Holberton School Project. It was built to mimic some of the basic functionality of the original Unix shell, to handle file redirections, command separator and logical operators. 
Compile using: gcc -Wall -Werror -Wextra -pedantic *.c -o hsh


## File Organization

| File Name           | Description                     |
| --------------------|---------------------------------|
| shell.h             | Header file                     |
| shell.c             | REPL and Command Prompt         |
| tokenizer.c         | Creates tokens from user input  |
| execute.c           | Command execution functions     |
| env_funcs.c         | Environment functions           |
| check_dir.c         | Checks directory path           |
| help_func.c         | String process helper functions |
| help_func_set2.c    | More helper functions           |
| func_stream_redir.c | Stream redirection functions    |
| builtins.c          | Built-in fuctions               |
| errors.c            | Error handling and messages     |
| putnchar.c          | Print process functions         |


## Usage Example
### Non-interactive mode
$ echo "ls" | ./hsh
$ echo "cat README.md; ls -l" | ./hsh

### Interactive mode
hsh$ ls
hsh$ cat README.md; ls -l


## Authors
This project is cloned from and modified based on shell v1 Brian has worked on before. Brian is the sole author of thie Shell V2 project because there is no peer for the second contributer in his cohort.
Brian Kong (Contributer of Shell V1, sole author of Shell V2)
Gunnar Bachelor (Contributer of V1)
