# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 23:12:59 by Cutku             #+#    #+#              #
#    Updated: 2023/06/09 01:35:32 by Cutku            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

MAIN_SRCS	= src/main/main.c

MAIN_OBJS	= $(MAIN_SRCS:.c=.o)

READLINE	= /Users/$(USER)/.brew/opt/readline/include/readline/readline/

INCL_RDL_HEADER	= -I /Users/$(USER)/.brew/opt/readline/include/readline/readline/
INCL_RDL_LIB	= -L /Users/$(USER)/.brew/opt/readline/lib -lreadline

LIBFT		= -L ./libft
LIBFT_FLAG	= -lft
LIBFT_LIB	= ./libft/libft.a

CC			= cc
RM			= rm -f
CFLAGS		= #-Wall -Werror -Wextra

NAME		= minishell

all: $(NAME)

$(LIBFT_LIB):
	make bonus -C ./libft && make clean -C ./libft
	echo "$(GREEN)Libft compiled successfully!$(DEF_COLOR)"

$(NAME): $(LIBFT_LIB) $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(MAIN_OBJS) $(LIBFT) $(LIBFT_FLAG) $(INCL_RDL_LIB) -o $(NAME)
	echo "$(GREEN)Minishell compiled successfully!$(DEF_COLOR)"

clean:
	$(RM) $(MAIN_OBJS)

fclean: clean
	# make fclean -C $(LIBFT)
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re