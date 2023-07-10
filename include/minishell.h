

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
# include <ctype.h>

//garbage_collector
void	*my_malloc(t_garbage **garbage, size_t count, size_t size);
void	add_garbage(t_garbage **first, void *ptr);
void	del_one_from_garbage(t_garbage **first, void *ptr);
void	clean_garbage(t_garbage **first);
void	del_node(t_garbage *del);
void	free_double_from_garbage(t_garbage **garbage, char **ptr);

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
void	add_env_var(t_shell *shell, char *var, char *value);
void	append_env_var(t_shell *shell, char *var, char *value);
void	delete_env_var(t_shell *shell, char *var);

// expansion
void	is_expandable(t_shell *shell);
void	merge_queue(t_shell *shell, t_token *token);
//helping functions
int		ft_double_strlen(char **str);
char	*shell_strdup(t_shell *shell, const char *s1);
char	*shell_strjoin(t_shell *shell, char const *s1, char const *s2);
char	*shell_substr(t_shell *shell, char const *s, int start, int len);

void	pipex(t_shell *shell, char **envp);
int	pipe_counter(t_shell *shell);
t_token	*find_right_token(t_shell *shell, int num_pipe);
void	handle_redirections(t_shell *shell, t_token *child, t_pipex *pipex);
void	exec_child_process(t_shell *shell,t_pipex *pipex, int i);
void	command_pointer(t_token *child, t_pipex *pipex);
void	create_child_process(t_shell *shell, t_pipex *pipex);

// Main process. File > pipex.c
void	create_pipelines(t_pipex *pipex, int num);
//Finding env-command path. File > get_paths.c
char	*get_command_path(t_pipex *pipex);
char	**get_env_path(char **envp);
char	*is_exact_path(t_pipex *pipex);
void	error_cmdpath(t_pipex *pipex);
//Here_doc. File > pipex_bonus.c
void	exec_here_doc(t_pipex *pipex, char **argv, int argc);
//Some usefull functions. File > pipex_utils.c
void	my_dup2(int input, int output, t_pipex *pipex);
void	my_waitpid(t_pipex *pipex);
int		open_file(char *filename, int flag, t_pipex *pipex);
//Parsing. File > parsing.c 
char	**ft_parser(char *string);
char	**word_lenght(char *string, int size);
void	remove_escape(char *str);
//Clean-up. File > clean_up.c
void	free_char_dubleptr(char **ptr);
void	free_int_dubleptr(int **ptr, int size);
void	close_pipes(t_pipex *pipex);
void	free_pipex(t_pipex *pipex);
void	input_dup2(int input);
void	output_dup2(int output);
#endif