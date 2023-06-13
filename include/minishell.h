

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <termcap.h>
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "struct.h"

//garbage_collector
void	*my_malloc(t_garbage **garbage, size_t count, size_t size);
void	add_garbage(t_garbage **first, void *ptr);
void	del_one_from_garbage(t_garbage **first, void *ptr);
void	clean_garbage(t_garbage **first);
void	del_node(t_garbage *del);

//Parsing
void	ft_isspace(t_shell *shell);
bool	is_output_redirection(t_shell *shell);
bool	is_input_redirection(t_shell *shell);
char	*quoted_word(t_shell *shell);
char	*non_quoted_word(t_shell *shell);
void	examine_type(t_shell *shell);
void	add_token_node(t_shell *shell, t_type type, char *str);
bool	is_word(t_shell *shell);
bool	is_heredoc(t_shell *shell);
bool	is_output_redirection_append(t_shell *shell);
bool	is_pipe(t_shell *shell);
//main
void	get_input(void);

void	s_quote_state(t_shell *shell);
void	d_quote_state(t_shell *shell);

#endif