/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:36:29 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/25 22:58:12 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

extern int	g_exit_status;

// Garbage_collector
void		*my_malloc(t_garbage **garbage, size_t count, size_t size);
void		add_to_garbage(t_garbage **first, void *ptr);
void		del_one_from_garbage(t_garbage **first, void *ptr);
void		clean_garbage(t_garbage **first);
void		del_node(t_garbage *del);

// Parsing
void		define_type(t_shell *shell);
bool		is_pipe(t_shell *shell, int	*i);
bool		is_word(t_shell *shell, int	*i);
bool		is_output_redirection(t_shell *shell, int *i);
bool		is_input_redirection(t_shell *shell, int *i);
bool		is_output_redirection_append(t_shell *shell, int *i);
bool		is_heredoc(t_shell *shell, int *i);

// Parsing states
void		single_quote_state(char *str, int *i);
void		double_quote_state(char *str, int *i);
void		skip_spaces(char *str, int *i);
int			ft_isspace(char a);

// Data_structures
void		add_token_node(t_shell *shell, t_type type, char *str);
void		add_token_next(t_shell *shell, t_token *token, \
t_type type, char *str);
char		*merge_queue(t_shell *shell);
void		enqueue(t_shell *shell, t_queue **front, t_queue **rear, void *ptr);
void		dequeue(t_shell *shell, t_queue **front);

// Main
int			execute_minishell(char **env);
void		exec_choice(t_shell *shell);
void		get_input_and_parse(t_shell *shell);
void		parse_the_input(t_shell *shell);
// Main -> utils
void		create_structure(t_shell *shell, char **env);
void		init_shell_struct(t_shell *shell);
void		if_exit_close_fd(t_shell *shell, char **str);
void		exec_choice(t_shell *shell);
int			check_syntax_error(t_shell *shell);

// Expansion
void		is_expandable(t_shell *shell);
void		s_quote_expand(t_shell *shell, char *str, int *i);
void		d_quote_expand(t_shell *shell, char *str, int *i, t_type *type);
void		non_quote_expand(t_shell *shell, char *str, int *i, t_type *type);
void		if_dollar_sign(t_shell *shell, char *str, int *i);
char		*value_of_expandable(t_shell *shell, char *var);
void		exit_code_expand(t_shell *shell, int *i);
void		variable_expand(t_shell *shell, char *str, int *i, \
int len_variable);
void		quote_removal(t_shell *shell, char *str, int *i);
void		non_quote_last(t_shell *shell, char *str, int *i);
void		delete_quotes(t_shell *shell);
void		split_after_expand(t_shell *shell);
int			extract_words(char *str, int *i);
t_token		*process_token(t_shell *shell, t_token *token, char *str, \
bool first);

/*********BUILTINS*********/

// Export.c
void		ft_export(t_shell *shell, char **str);
void		export_operations(t_shell *shell, char **str, int i);
void		export_to_env(t_shell *shell, char *str, int append, char *key);
void		export_to_exp_list(t_shell *shell, char *str, int append, \
char *key);
void		add_to_export(t_shell *shell, char *key, char *value);
void		append_to_export(t_shell *shell, char *key, char *value);
void		update_export_list(t_shell *shell, char *key, char *value);
void		del_node_from_export(t_shell *shell, t_export *del);
void		del_one_from_export(t_shell *shell, char *key);
void		create_export_list(t_shell *shell);
t_export	*check_export_list(t_shell *shell, char *str);
void		print_export_list(t_shell *shell);
// Cd.c
void		ft_cd(t_shell *shell, char *path);
void		update_oldpwd(t_shell *shell, char *current_pwd);
// Echo.c
void		ft_echo(char **str);
int			check_echo_flag(char *str);
// Env.c
void		ft_env(t_shell *shell, char **str);
void		create_env(t_shell *shell, char **env);
int			ft_getenv(char **str, char *var);
// Env.c -> operations
void		update_env_var(t_shell *shell, char *var, char *value);
void		add_env_var(t_shell *shell, char *var, char *value);
void		append_env_var(t_shell *shell, char *var, char *value);
void		delete_env_var(t_shell *shell, char *var);
// Exit.c
void		ft_exit(t_shell *shell, char **str);
void		free_shell(t_shell *shell);
void		exit_non_numeric(t_shell *shell, char **str);
void		exit_no_arg(t_shell *shell, char **str);
// Pwd.c
void		ft_pwd(char **str);
// Unset.c
void		ft_unset(t_shell *shell, char **str);
int			is_valid_syntax_var(char *str);

// Heredoc queue
void		exec_order(t_shell *shell);
bool		order_heredoc(t_shell *shell);
bool		is_syntax_error(t_token *token);
// Heredoc.c
void		here_doc(t_shell *shell);
int			heredoc_strlen(char *str);
int			delimiter_str_cmp(char *del, char *str);
char		*heredoc_file_name(t_shell *shell, int counter);
void		unlink_heredocs(t_shell *shell);
void		heredoc_expand(t_shell *shell, char *str);
void		change_token_values(t_shell *shell, t_token *token, char *file);
int			execute_heredoc(t_shell *shell, t_token *temp_token, int fd);

// Utils functions
int			ft_double_strlen(char **str);
char		*shell_strdup(t_shell *shell, const char *s1);
char		*shell_strjoin(t_shell *shell, char const *s1, char const *s2);
char		*shell_substr(t_shell *shell, char const *s, int start, int len);
int			ft_strcmp(char *str1, char *str2);

// Clean_up.c
void		free_char_dubleptr(char **ptr);
void		free_int_dubleptr(int **ptr, int size);
void		close_pipes(t_pipex *pipex);

// Finding env-command path. File > get_paths.c
char		*get_command_path(t_pipex *pipex);
char		**get_env_path(char **envp);
char		*is_exact_path(t_pipex *pipex);
void		add_slash_to_path(t_pipex *pipex);
// Exec.c
void		pipex(t_shell *shell);
void		create_child_process(t_shell *shell, t_pipex *pipex);
void		create_pipelines(t_pipex *pipex, int num);
void		exec_child_process(t_shell *shell, t_pipex *pipex, int i);

// Exec -> builtins
int			is_builtin(char *str);
void		which_builtin(t_shell *shell, char **str);
void		exec_builtin(t_shell *shell, char **str, t_pipex *pipex);

// Exec -> redirections
bool		handle_redirections(t_pipex *pipex, t_token *token, int flag);
bool		do_redirections(t_pipex *pipex, t_token *child, int flag);
void		pipe_redirections(t_pipex *pipex, int i);
bool		check_ambiguous_redirect(t_pipex *pipex, t_token *child, int flag);

// Exec -> utils
void		initialize_pipex(t_pipex *pipex);
int			pipe_counter(t_shell *shell);
t_token		*find_right_token(t_shell *shell, int num_pipe);
void		free_pipex_all(t_pipex *pipex);
void		free_pipex_all_two(t_pipex *pipex);
void		my_waitpid(t_pipex *pipex);
char		**command_pointer(t_token *child);

// Exec -> file redirections
void		input_dup2(int input, t_pipex *pipex, int flag);
void		output_dup2(int output, t_pipex *pipex, int flag);
int			open_file(t_pipex *pipex, char *filename, int rdir, int flag);
int			open_input_file(t_pipex *pipex, char *filename, int flag);

// Signals
void		signals(t_shell *shell);
void		signals_child(void);
void		setup_termios(t_shell *shell);

// Error messages
void		error_not_valid_identifier(char *str1, char *str2);
void		error_invalid_option(char **str);
void		error_printer(char *str1, char *str2, char *str3);
void		error_permission(t_pipex *pipex);
void		error_cmdpath(t_pipex *pipex);
void		is_directory(t_pipex *pipex);

#endif