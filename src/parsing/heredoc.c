/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:35:43 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/19 07:14:29 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
