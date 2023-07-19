

DEF_COLOR = \033[0;39m
RED = \033[0;91m
GREEN = \033[0;32m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

.SILENT:

# USER		= $(shell whoami)

MAIN_SRC	= src/main/main.c src/garbage_collector/add_to_garbage.c src/garbage_collector/del_from_garbage.c \
			src/garbage_collector/my_malloc.c src/execution/priority.c help_function.c \
			src/expansion/expand_new.c src/execution/clean_up.c src/execution/exec.c \
			src/execution/file_redirections.c src/execution/get_paths.c src/execution/exec_builtin.c heredoc.c \
			src/expansion/remove_quotes.c


PARSE_SRC	=	src/parsing/heredoc.c \
				src/parsing/redirections.c \
				src/parsing/tokenizer.c

BUILTIN_SRC	=	src/builtins/cd.c src/builtins/env.c src/builtins/exit.c src/builtins/export/export.c src/builtins/unset.c \
				src/builtins/echo.c src/builtins/pwd.c src/builtins/export/export_list.c
BUILTIN_OBJ	=	$(BUILTIN_SRC:.c=.o)

DATA_ST_SRC =	src/data_structures/linked_list.c \
				src/data_structures/queue.c \
				src/data_structures/merge_queue.c
DATA_ST_OBJ	=	$(DATA_ST_SRC:.c=.o)

MAIN_OBJ	= $(MAIN_SRC:.c=.o)
PARSE_OBJ	= $(PARSE_SRC:.c=.o)

INCL_RDL_HEADER	= -I /Users/$(USER)/.brew/opt/readline/include
INCL_RDL_LIB	= -L /Users/$(USER)/.brew/opt/readline/lib
READLINE_LIB	=	-lreadline

LIBFT		= ./libft
LIBFT_LIB	= ./libft/libft.a

CC			= cc
RM			= rm -f
CFLAGS		= $(INCL_RDL_HEADER) -g #-Wall -Werror -Wextra

NAME		= minishell

all: $(NAME)

$(LIBFT_LIB):
	make bonus -C $(LIBFT) && make clean -C $(LIBFT)
	echo "$(GREEN)Libft compiled successfully!$(DEF_COLOR)"

$(NAME): $(LIBFT_LIB) $(MAIN_OBJ) $(PARSE_OBJ) $(BUILTIN_OBJ) $(DATA_ST_OBJ)
	$(CC) $(CFLAGS) $(PARSE_OBJ) $(BUILTIN_OBJ) $(DATA_ST_OBJ) $(MAIN_OBJ) $(LIBFT_LIB) $(INCL_RDL_LIB) $(READLINE_LIB) -o $(NAME)
	echo "$(GREEN)Minishell compiled successfully!$(DEF_COLOR)"

clean:
	$(RM) $(MAIN_OBJ) 
	$(RM) $(PARSE_OBJ)
	$(RM) $(BUILTIN_OBJ)

fclean: clean
	make fclean -C $(LIBFT)
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re