/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 03:08:29 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/25 20:48:30 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# define SYMBOLS "<>|"
# define WORD_DELIMITERS "<>| \0"

# define SYNTAX_ERR_MSG	"Minishell: syntax error near unexpected token `"
# define NO_FILE		": No such file or directory"
# define NO_PERM		": Permission denied"
# define DIR_ERR		": is a directory"
# define NO_CMD			": command not found"
# define EXIT_NON_NUM	": numeric argument required"
# define TOO_MNY_ARG	"too many arguments"

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
	Q_DELIMITER,
	AMBIGIOUS_R,
}t_type;

typedef struct s_token
{
	t_type			type;
	int				index;
	char			*str;
	struct s_token	*next;
}t_token;

typedef struct s_export
{
	char			*key;
	char			*value;
	struct s_export	*next;
}t_export;

typedef struct s_queue
{
	void			*content;
	struct s_queue	*next;
}	t_queue;

typedef struct s_pipex
{
	pid_t	*pid;
	char	**command;
	char	**all_paths;
	int		**pipeline;
	char	**envp;
	char	*cmd_path;
	int		num_commands;
}	t_pipex;

typedef struct s_shell
{
	int				num_pipe;
	int				term_fd[2];
	int				num_heredoc;
	char			*input;
	char			**my_env;
	struct termios	termios;
	t_pipex			*pipex;
	t_garbage		*garbage;
	t_token			*token;
	t_queue			*front;
	t_queue			*rear;
	t_queue			*exp_front;
	t_queue			*exp_rear;
	t_export		*export_list;
}	t_shell;

#endif