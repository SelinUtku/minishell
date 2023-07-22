/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_after_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 04:50:17 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/22 20:40:57 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	split_after_expand(t_shell *shell)
{
	t_token	*token;
	bool	first;

	token = shell->token;
	while (token)
	{
		first = true;
		token = process_token(shell, token, token->str, first);
		token = token->next;
	}
}

int	extract_words(char *str, int *i)
{
	int	start;

	start = (*i);
	while (!ft_isspace(str[*i]) && str[*i] != '\0')
	{
		if (str[*i] == '\'')
			single_quote_state(str, i);
		else if (str[*i] == '\"')
			double_quote_state(str, i);
		else
			(*i)++;
	}
	return ((*i) - start);
}

t_token	*process_token(t_shell *shell, t_token *token, char *str, bool first)
{
	int		i;
	int		start;
	int		len_word;

	i = 0;
	while (str && str[i] != '\0')
	{
		skip_spaces(str, &i);
		start = i;
		len_word = extract_words(str, &i);
		skip_spaces(str, &i);
		if (first)
			token->str = shell_substr(shell, str, start, len_word);
		else
		{
			add_token_next(shell, token, token->type, \
			shell_substr(shell, str, start, len_word));
			token = token->next;
		}
		first = false;
	}
	if (first == false)
		del_one_from_garbage(&shell->garbage, str);
	return (token);
}
