/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:23:52 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/19 08:34:25 by Cutku            ###   ########.fr       */
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
			;
		else if (is_output_redirection(shell, &i))
			;
		else if (is_heredoc(shell, &i))
			;
		else if (is_output_redirection_append(shell, &i))
			;
		else if (is_pipe(shell, &i))
			;
		else if (is_word(shell, &i))
			;
		ft_isspace(shell->input, &i);
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

int	ft_isspace(char *str, int *i)
{
	while (str[(*i)] == 32 && str[(*i)] != '\0')
		(*i)++;
	return (*i);
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

void	single_quote_state(char *str, int *i)
{
	(*i)++;
	while (str[(*i)] != '\'' && str[(*i)] != '\0')
		(*i)++;
	if (str[(*i)] == '\'')
		(*i)++;
}

void	double_quote_state(char *str, int *i)
{
	(*i)++;
	while (str[(*i)] != '\"' && str[(*i)] != '\0')
		(*i)++;
	if (str[(*i)] == '\"')
		(*i)++;
}
