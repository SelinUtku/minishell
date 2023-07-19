

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
void	define_type(t_shell *shell);
int		ft_isspace(char *str, int *i);
bool	is_pipe(t_shell *shell, int	*i);
bool	is_word(t_shell *shell, int	*i);
bool	is_output_redirection(t_shell *shell, int *i);
bool	is_input_redirection(t_shell *shell, int *i);
bool	is_output_redirection_append(t_shell *shell, int *i);
bool	is_heredoc(t_shell *shell, int *i);

//data_structures
void	add_token_node(t_shell *shell, t_type type, char *str);
void	add_token_next(t_shell *shell, t_token *token, t_type type, char *str);
void	merge_queue(t_shell *shell, t_token *token);
//main
int		get_input(char **env);

void	single_quote_state(char *str, int *i);
void	double_quote_state(char *str, int *i);

//builtins

void	create_env(t_shell *shell, char **env);
void	ft_env(t_shell *shell, char **str);
int		ft_getenv(char **str, char *var);
char	*value_of_expandable(t_shell *shell, char *var);
void	ft_pwd(t_shell *shell);
void	ft_cd(t_shell *shell, char *path);
void	ft_exit(t_shell *shell, char **str);
void	update_oldpwd(t_shell *shell);
void	ft_export(t_shell *shell, char **str);
void	update_env_var(t_shell *shell, char *var, char *value);
void	add_env_var(t_shell *shell, char *var, char *value);
void	append_env_var(t_shell *shell, char *var, char *value);
void	delete_env_var(t_shell *shell, char *var);
void	ft_unset(t_shell *shell, char **str);
void	del_node_from_list(t_shell *shell, t_export *del);
void	del_one_list(t_shell *shell, char *key);
void	print_export_list(t_shell *shell);
void	create_export_list(t_shell *shell);

// expansion
void	is_expandable(t_shell *shell);
//helping functions
int		ft_double_strlen(char **str);
char	*shell_strdup(t_shell *shell, const char *s1);
char	*shell_strjoin(t_shell *shell, char const *s1, char const *s2);
char	*shell_substr(t_shell *shell, char const *s, int start, int len);

void	pipex(t_shell *shell, char **envp);
int		pipe_counter(t_shell *shell);
t_token	*find_right_token(t_shell *shell, int num_pipe);
void	handle_redirections(t_shell *shell, t_token *child);
void	exec_child_process(t_shell *shell,t_pipex *pipex, int i);
char	**command_pointer(t_token *child);
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
void	my_waitpid(t_shell *shell,t_pipex *pipex);
int		open_file(char *filename, int flag);
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
int		which_builtin(t_shell *shell, char **str);
void	ft_echo(t_shell *shell, char **str);
void	exec_builtin(t_shell *shell, char **str, t_pipex *pipex);
int		is_builtin(char *str);
void	here_doc(t_shell *shell);
void	dollar_func(t_shell *shell, char *str, int *i);
void	unlink_heredocs(t_shell *shell);
int		ft_strcmp(char *str1, char *str2);
void	error_not_valid_identifier(t_shell *shell, char *str1, char *str2);
void	error_invalid_option(t_shell *shell, char **str);
void	add_list(t_shell *shell, char *key, char *value);
int		check_list(t_shell *shell, char *str, char *value);
int		is_valid_syntax_var(t_shell *shell, char *str);
void	split_after_expand(t_shell *shell);
void	delete_quotes(t_shell *shell);
#endif