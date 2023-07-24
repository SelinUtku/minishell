

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

MAIN_SRC	=	src/main/main.c  src/execution/priority.c \
			src/execution/clean_up.c src/execution/exec.c \
			src/execution/file_redirections.c src/execution/get_paths.c \
			src/execution/exec_builtin.c src/execution/heredoc/heredoc.c \
			src/signals/signal.c src/execution/heredoc/heredoc_utils.c
MAIN_OBJ	=	$(MAIN_SRC:.c=.o)

GARBAGE_SRC	=	src/garbage_collector/add_to_garbage.c \
				src/garbage_collector/del_from_garbage.c \
				src/garbage_collector/my_malloc.c
GARBAGE_OBJ =	$(GARBAGE_SRC:.c=.o)

PARSE_SRC	=	src/parsing/parsing_states.c \
				src/parsing/redirections.c \
				src/parsing/tokenizer.c
PARSE_OBJ	=	$(PARSE_SRC:.c=.o)

EXPAND_SRC	=	src/expansion/expand.c \
				src/expansion/remove_quotes.c \
				src/expansion/expansion_states.c \
				src/expansion/split_after_expand.c
EXPAND_OBJ	=	$(EXPAND_SRC:.c=.o)

BUILTIN_SRC	=	src/builtins/cd.c src/builtins/env.c src/builtins/exit.c \
				src/builtins/export/export.c src/builtins/unset.c \
				src/builtins/echo.c src/builtins/pwd.c src/builtins/export/export_list.c \
				src/builtins/export/export_operations.c
BUILTIN_OBJ	=	$(BUILTIN_SRC:.c=.o)

DATA_ST_SRC =	src/data_structures/linked_list.c \
				src/data_structures/queue.c \
				src/data_structures/merge_queue.c
DATA_ST_OBJ	=	$(DATA_ST_SRC:.c=.o)

UTILS_SRC	=	src/utils/error_messages.c \
				src/utils/help_functions.c \
				src/utils/help_functions2.c
UTILS_OBJ	=	$(UTILS_SRC:.c=.o)

ENV_OP_SRC	=	src/environment_operations/environment_operations.c
ENV_OP_OBJ	=	$(ENV_OP_SRC:.c=.o)

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

$(NAME): $(LIBFT_LIB) $(MAIN_OBJ) $(PARSE_OBJ) $(BUILTIN_OBJ) $(DATA_ST_OBJ) $(GARBAGE_OBJ) $(EXPAND_OBJ) $(UTILS_OBJ) $(ENV_OP_OBJ)
	$(CC) $(CFLAGS) $(PARSE_OBJ) $(BUILTIN_OBJ) $(DATA_ST_OBJ) $(GARBAGE_OBJ) $(MAIN_OBJ) $(LIBFT_LIB) \
	$(INCL_RDL_LIB) $(READLINE_LIB) $(EXPAND_OBJ) $(UTILS_OBJ) $(ENV_OP_OBJ) -o $(NAME)
	echo "$(GREEN)Minishell compiled successfully!$(DEF_COLOR)"

clean:
	$(RM) $(MAIN_OBJ) 
	$(RM) $(PARSE_OBJ)
	$(RM) $(BUILTIN_OBJ)
	$(RM) $(DATA_ST_OBJ)
	$(RM) $(GARBAGE_OBJ)
	$(RM) $(EXPAND_OBJ)
	$(RM) $(UTILS_OBJ)
	$(RM) $(ENV_OP_OBJ)

fclean: clean
	make fclean -C $(LIBFT)
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re