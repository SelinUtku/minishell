/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:37:59 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/06 00:20:10 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_output_redirection(t_shell *shell)
{
	if (shell->input[shell->i] == '>' && shell->input[shell->i + 1] != '>')
	{
		add_token_node(shell, OUTPUT_R, shell_strdup(shell, ">"));
		shell->i++;
		return (true);
	}
	return (false);
}

bool	is_input_redirection(t_shell *shell)
{
	if (shell->input[shell->i] == '<' && shell->input[shell->i + 1] != '<')
	{
		add_token_node(shell, INPUT_R, shell_strdup(shell, "<"));
		shell->i++;
		return (true);
	}
	return (false);
}

bool	is_output_redirection_append(t_shell *shell)
{
	char	*str;

	if (shell->input[shell->i] == '>' && shell->input[shell->i + 1] == '>')
	{
		add_token_node(shell, OUTPUT_R_APPEND, shell_strdup(shell, ">>"));
		shell->i += 2;
		return (true);
	}
	return (false);
}
