/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:23:52 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/25 21:09:59 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	define_type(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->input[i] != '\0')
	{
		if (is_input_redirection(shell, &i))
			skip_spaces(shell->input, &i);
		else if (is_output_redirection(shell, &i))
			skip_spaces(shell->input, &i);
		else if (is_heredoc(shell, &i))
			skip_spaces(shell->input, &i);
		else if (is_output_redirection_append(shell, &i))
			skip_spaces(shell->input, &i);
		else if (is_pipe(shell, &i))
			skip_spaces(shell->input, &i);
		else if (is_word(shell, &i))
			skip_spaces(shell->input, &i);
		else
			skip_spaces(shell->input, &i);
	}
}

bool	is_pipe(t_shell *shell, int	*i)
{
	if (shell->input[(*i)] == '|')
	{
		add_token_node(shell, PIPE, shell_strdup(shell, "|"));
		(*i)++;
		return (true);
	}
	return (false);
}

bool	is_word(t_shell *shell, int	*i)
{
	int		start;
	char	*str;

	if (ft_strchr(WORD_DELIMITERS, shell->input[(*i)]) == 0)
	{
		start = *i;
		while (ft_strchr(WORD_DELIMITERS, shell->input[(*i)]) == 0)
		{
			if (shell->input[(*i)] == '\'')
				single_quote_state(shell->input, i);
			else if (shell->input[(*i)] == '\"')
				double_quote_state(shell->input, i);
			else
				(*i)++;
		}
		str = shell_substr(shell, shell->input, start, (*i) - start);
		add_token_node(shell, WORD, str);
		return (true);
	}
	return (false);
}
