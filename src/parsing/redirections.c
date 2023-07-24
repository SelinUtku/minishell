/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:37:59 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/24 23:07:11 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_output_redirection(t_shell *shell, int *i)
{
	if (shell->input[(*i)] == '>' && shell->input[(*i) + 1] != '>')
	{
		add_token_node(shell, OUTPUT_R, shell_strdup(shell, ">"));
		(*i)++;
		return (true);
	}
	return (false);
}

bool	is_input_redirection(t_shell *shell, int *i)
{
	if (shell->input[(*i)] == '<' && shell->input[(*i) + 1] != '<')
	{
		add_token_node(shell, INPUT_R, shell_strdup(shell, "<"));
		(*i)++;
		return (true);
	}
	return (false);
}

bool	is_output_redirection_append(t_shell *shell, int *i)
{
	if (shell->input[(*i)] == '>' && shell->input[(*i) + 1] == '>')
	{
		add_token_node(shell, OUTPUT_R_APPEND, shell_strdup(shell, ">>"));
		(*i) += 2;
		return (true);
	}
	return (false);
}

bool	is_heredoc(t_shell *shell, int *i)
{
	if (shell->input[(*i)] == '<' && shell->input[(*i) + 1] == '<')
	{
		add_token_node(shell, HEREDOC, shell_strdup(shell, "<<"));
		(*i) += 2;
		return (true);
	}
	return (false);
}
