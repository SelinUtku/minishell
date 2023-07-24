/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 02:41:30 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/24 23:12:22 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	quote_removal(t_shell *shell, char *str, int *i)
{
	int	start;
	int	quote;

	quote = str[(*i)];
	(*i)++;
	start = *i;
	if (str[(*i)] == quote)
		enqueue(shell, &shell->exp_front, &shell->exp_rear, \
		shell_substr(shell, str, start, *i - start));
	while (str[*i] != quote && str[*i] != '\0')
		(*i)++;
	if (*i != start)
		enqueue(shell, &shell->exp_front, &shell->exp_rear, \
		shell_substr(shell, str, start, *i - start));
	if (str[*i] == quote)
		(*i)++;
}

void	non_quote_last(t_shell *shell, char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] != '\"' && str[*i] != '\'' && str[*i] != '\0')
		(*i)++;
	if (*i != start)
		enqueue(shell, &shell->exp_front, &shell->exp_rear, \
		shell_substr(shell, str, start, *i - start));
}

void	delete_quotes(t_shell *shell)
{
	t_token	*temp_token;
	int		i;

	temp_token = shell->token;
	while (temp_token)
	{
		i = 0;
		while (temp_token->str && temp_token->str[i])
		{
			if (temp_token->str[i] == '\'' || temp_token->str[i] == '\"')
				quote_removal(shell, temp_token->str, &i);
			else
				non_quote_last(shell, temp_token->str, &i);
		}
		del_one_from_garbage(&shell->garbage, temp_token->str);
		temp_token->str = merge_queue(shell);
		temp_token = temp_token->next;
	}
}
