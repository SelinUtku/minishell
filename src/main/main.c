/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 04:02:59 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/25 19:30:47 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_syntax_error(t_shell *shell)
{
	t_token	*temp;

	temp = shell->token;
	while (temp)
	{
		if (temp->type == SYNTAX_ERROR)
			return (shell->status = 258, 1);
		temp = temp->next;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 1 && argv)
	{
		write (2, "Minishell does not take any arguments\n", 39);
		return (1);
	}
	else
	{
		return (get_input(env));
	}
	return (0);
}

void	init_shell_struct(t_shell *shell)
{
	shell->token = NULL;
	shell->front = NULL;
	shell->rear = NULL;
	shell->exp_front = NULL;
	shell->exp_rear = NULL;
}


int	get_input(char **env)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (0);
	shell->status = 0;
	shell->garbage = NULL;
	shell->export_list = NULL;
	init_shell_struct(shell);
	create_env(shell, env);
	create_export_list(shell);
	while (1)
	{
		init_shell_struct(shell);
		signals(shell);
		if (isatty(fileno(stdin)))
			shell->input = readline("MinisHell$ ");
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			shell->input = ft_strtrim(line, "\n");
			free(line);
		}
		// shell->input = readline("MinisHELL$ ");
		// ft_exit(shell);
		if (shell->input == NULL || shell->input[0] == EOF)
			exit(shell->status);
		add_history(shell->input);
		define_type(shell);
		exec_order(shell);
		is_expandable(shell);
		split_after_expand(shell);
		delete_quotes(shell);
		here_doc(shell);
		shell->num_pipe = pipe_counter(shell);
		if (check_syntax_error(shell) == 0)
			exec_choice(shell);
		unlink_heredocs(shell);
		free(shell->input);
	}
	clean_garbage(&shell->garbage);
	return (shell->status);

}

void	exec_choice(t_shell *shell)
{
	char	**str;
	bool	flag;

	if (shell->num_pipe == 0)
	{
		str = command_pointer(shell->token);
		if (str && is_builtin(*str))
		{
			shell->term_fd[0] = dup(STDIN_FILENO);
			shell->term_fd[1] = dup(STDOUT_FILENO);
			flag = handle_redirections(shell, NULL, shell->token, 0);
			if (is_builtin(*str) == 4)
			{
				close(shell->term_fd[0]);
				close(shell->term_fd[1]);
			}
			if (flag)
				which_builtin(shell, str);
			input_dup2(shell->term_fd[0], NULL, 0);
			output_dup2(shell->term_fd[1], NULL, 0);
		}
		else
			pipex(shell);
		free(str);
	}
	else
		pipex(shell);
}
