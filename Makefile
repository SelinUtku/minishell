

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

MAIN_SRC	= src/main/main.c \

PARSE_SRC	= src/parsing/heredoc.c \
				src/parsing/quote_check.c \
				src/parsing/redirections.c \
				src/parsing/tokenizer.c

MAIN_OBJ	= $(MAIN_SRC:.c=.o)
PARSE_OBJ	= $(PARSE_SRC:.c=.o)

READLINE	= /Users/$(USER)/.brew/opt/readline/include/readline/readline/

INCL_RDL_HEADER	= -I /Users/$(USER)/.brew/opt/readline/include/readline/readline/
INCL_RDL_LIB	= -L /Users/$(USER)/.brew/opt/readline/lib -lreadline

LIBFT		= ./libft
LIBFT_LIB	= ./libft/libft.a

CC			= cc
RM			= rm -f
CFLAGS		= #-Wall -Werror -Wextra

NAME		= minishell

all: $(NAME)

$(LIBFT_LIB):
	make bonus -C $(LIBFT) && make clean -C $(LIBFT)
	echo "$(GREEN)Libft compiled successfully!$(DEF_COLOR)"

$(NAME): $(LIBFT_LIB) $(MAIN_OBJ) $(PARSE_OBJ)
	$(CC) $(CFLAGS) $(PARSE_OBJ) $(MAIN_OBJ) $(LIBFT_LIB) $(INCL_RDL_LIB) -o $(NAME)
	echo "$(GREEN)Minishell compiled successfully!$(DEF_COLOR)"

clean:
	$(RM) $(MAIN_OBJ) 
	$(RM) $(PARSE_OBJ)

fclean: clean
	make fclean -C $(LIBFT)
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re