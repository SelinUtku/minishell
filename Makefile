# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 23:12:59 by Cutku             #+#    #+#              #
#    Updated: 2023/06/08 23:16:29 by Cutku            ###   ########.fr        #
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

MAIN_SRCS	= main.c

MAIN_OBJS = $(MAIN_SRCS:.c=.o)

LIBFT		= ./libft/
LIBFT_LIB	= ./libft/libft.a

CC			= cc
RM			= rm -f
CFLAGS		= -Wall -Werror -Wextra

NAME		= minishell

all: $(NAME)

$(LIBFT_LIB):
	make bonus -C $(LIBFT) && make clean -C $(LIBFT)
	echo "$(GREEN)Libft compiled successfully!$(DEF_COLOR)"

$(NAME): $(MAIN_OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(MAIN_OBJS) $(LIBFT_LIB) -o $(NAME)
	echo "$(GREEN)Minishell compiled successfully!$(DEF_COLOR)"

clean:
	$(RM) $(MAIN_OBJS)

fclean: clean
	make fclean -C $(LIBFT)
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re