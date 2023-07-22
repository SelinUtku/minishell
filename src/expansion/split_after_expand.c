/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_after_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 04:50:17 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/22 04:25:42 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	split_after_expand(t_shell *shell)
{
	t_token	*temp_token;

	temp_token = shell->token;
	while (temp_token)
	{
		if (count_words(temp_token->str) > 1)
			temp_token = process_token(shell, temp_token);
		temp_token = temp_token->next;
	}
}

void	extract_words(char *str, int *i)
{
	while (!ft_isspace(str[*i]) && str[*i] != '\0')
	{
		if (str[*i] == '\'')
			single_quote_state(str, i);
		else if (str[*i] == '\"')
			double_quote_state(str, i);
		else
			(*i)++;
	}
}

t_token	*process_token(t_shell *shell, t_token *token)
{
	int		i;
	bool	first_time;
	int		start;
	char	*str;

	str = token->str;
	i = 0;
	first_time = true;
	while (str && str[i] != '\0')
	{
		skip_spaces(str, &i);
		start = i;
		extract_words(str, &i);
		if (first_time)
			token->str = shell_substr(shell, str, start, i - start);
		else
		{
			add_token_next(shell, token, token->type, \
			shell_substr(shell, str, start, i - start));
			token = token->next;
		}
		first_time = false;
	}
	del_one_from_garbage(&shell->garbage, str);
	return (token);
}

int	count_words(char *str)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (str && str[i] != '\0')
	{
		while (str && (str[i] == 32 || str[i] == 9 || str[i] == 10))
			i++;
		if (str[i] != '\0')
			counter++;
		while (str[i] != 32 && str[i] != 9 && str[i] != 10 && str[i] != '\0')
		{
			if (str[i] == '\'')
				single_quote_state(str, &i);
			else if (str[i] == '\"')
				double_quote_state(str, &i);
			else
				i++;
		}
	}
	return (counter);
}
