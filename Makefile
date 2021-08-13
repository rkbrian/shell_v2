# name of the executable: hsh
# rules: all, clean

# clean: deletes the executable

# NAME: the name of the executable
# SRC: the .c files listed

NAME = hsh
SRC = \
builtins.c \
check_dir.c \
env_funcs.c \
errors.c \
execute.c \
func_stream_redir.c \
help_func.c \
help_func_set2.c \
putnchar.c \
shell.c \
tokenizer.c

all: $(NAME)

hsh: $(files)
	gcc -Wall -Werror -Wextra -pedantic $(SRC) -o hsh
clean:
	rm $(NAME)
.PHONY: hsh all clean
