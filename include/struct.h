/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 03:08:29 by Cutku             #+#    #+#             */
/*   Updated: 2023/06/29 03:09:26 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef STRUCT_H
# define STRUCT_H
# define SYMBOLS "<>|"
# define WORD_DELIMITERS "<>| \0"

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;

}	t_garbage;

typedef enum e_type
{
	HEREDOC,
	INPUT_R,
	OUTPUT_R,
	OUTPUT_R_APPEND,
	DELIMITER,
	FILENAME,
	PIPE,
	WORD,
	SYNTAX_ERROR,
}t_type;

typedef struct s_token
{
	t_type			type;
	int				index;
	struct s_token	*prev;
	struct s_token	*next;
	char			*str;
}t_token;

typedef struct s_queue
{
	t_token			*token;
	struct s_queue	*next;
}	t_queue;

typedef struct s_queue_exp
{
	char			*str;
	struct s_queue_exp	*next;
}	t_queue_exp;

typedef struct s_shell
{
	int			i;
	char		*input;
	char		**my_env;
	t_garbage	*garbage;
	t_token		*token;
	t_queue		*front;
	t_queue		*rear;
	t_queue_exp	*exp_queue;
}t_shell;


void	enqueue(t_queue **front, t_queue **rear, t_token *ptr);
void	dequeue(t_queue **front);
void	exec_order(t_shell *shell);
bool	order_heredoc(t_shell *shell, t_token *token);
void	order_redirections(t_shell *shell, t_token *token);
bool	is_syntax_error(t_shell *shell, t_token *token);

#endif
