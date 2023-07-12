

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
			src/garbage_collector/my_malloc.c src/execution/priority.c src/execution/queue.c help_function.c \
			src/expansion/expand.c src/expansion/merge_queue.c src/execution/clean_up.c src/execution/exec.c \
			src/execution/file_redirections.c src/execution/get_paths.c src/execution/exec_builtin.c 

PARSE_SRC	=	src/parsing/heredoc.c \
				src/parsing/redirections.c \
				src/parsing/tokenizer.c

BUILTIN_SRC	= src/builtins/cd.c src/builtins/env.c src/builtins/exit.c src/builtins/export.c src/builtins/unset.c \
			 src/builtins/echo.c src/builtins/pwd.c
BUILTIN_OBJ	= $(BUILTIN_SRC:.c=.o)

MAIN_OBJ	= $(MAIN_SRC:.c=.o)
PARSE_OBJ	= $(PARSE_SRC:.c=.o)

READLINE	= /Users/$(USER)/.brew/opt/readline/include/readline/readline/

INCL_RDL_HEADER	= -I /Users/$(USER)/.brew/opt/readline/include/readline/readline/
INCL_RDL_LIB	= -L /Users/$(USER)/.brew/opt/readline/lib -lreadline

LIBFT		= ./libft
LIBFT_LIB	= ./libft/libft.a

CC			= cc
RM			= rm -f
CFLAGS		= -g #-Wall -Werror -Wextra

NAME		= minishell

all: $(NAME)

$(LIBFT_LIB):
	make bonus -C $(LIBFT) && make clean -C $(LIBFT)
	echo "$(GREEN)Libft compiled successfully!$(DEF_COLOR)"

$(NAME): $(LIBFT_LIB) $(MAIN_OBJ) $(PARSE_OBJ) $(BUILTIN_OBJ)
	$(CC) $(CFLAGS) $(PARSE_OBJ) $(BUILTIN_OBJ) $(MAIN_OBJ) $(LIBFT_LIB) $(INCL_RDL_LIB) -o $(NAME)
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