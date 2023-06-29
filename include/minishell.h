

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
void	get_input(char **env);

void	s_quote_state(t_shell *shell);
void	d_quote_state(t_shell *shell);

//builtins

void	create_env(t_shell *shell, char **env);
void	ft_env(t_shell *shell);
int		ft_getenv(char **str, char *var);
char	*value_of_expandable(t_shell *shell, char *var);
void	ft_pwd(void);
void	ft_cd(t_shell *shell, char *path);
void	ft_exit(t_shell *shell);
void	update_oldpwd(t_shell *shell);
void	ft_export(t_shell *shell, char *var, char *value);
void	update_env_var(t_shell *shell, char *var, char *value);
void	create_env_var(t_shell *shell, char *var, char *value);
void	append_env_var(t_shell *shell, char *var, char *value);
void	delete_env_var(t_shell *shell, char *var);

// expansion
void	is_expandable(t_shell *shell);
void	exp_enqueue(t_queue_exp **front, t_queue_exp **rear, char *ptr);
void	exp_dequeue(t_queue_exp **front);
char	*merge_queue(t_shell *shell, t_queue_exp **temp_front, t_queue_exp **temp_rear);
//helping functions
int		ft_double_strlen(char **str);
#endif