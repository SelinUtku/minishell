/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:21:52 by sutku             #+#    #+#             */
/*   Updated: 2023/07/25 21:03:30 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_structure(t_shell *shell, char **env)
{
	g_exit_status = 0;
	shell->garbage = NULL;
	shell->export_list = NULL;
	init_shell_struct(shell);
	create_env(shell, env);
	create_export_list(shell);
}

void	init_shell_struct(t_shell *shell)
{
	shell->token = NULL;
	shell->front = NULL;
	shell->rear = NULL;
	shell->exp_front = NULL;
	shell->exp_rear = NULL;
}

void	if_exit_close_fd(t_shell *shell, char **str)
{
	if (is_builtin(*str) == 4)
	{
		close(shell->term_fd[0]);
		close(shell->term_fd[1]);
	}
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
			flag = handle_redirections(NULL, shell->token, 0);
			if_exit_close_fd(shell, str);
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

int	check_syntax_error(t_shell *shell)
{
	t_token	*temp;

	temp = shell->token;
	while (temp)
	{
		if (temp->type == SYNTAX_ERROR)
			return (g_exit_status = 258, 1);
		temp = temp->next;
	}
	return (0);
}
