/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 02:41:30 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/19 06:52:03 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	s_quote_last(t_shell *shell, char *str, int *i)
{
	int		start;

	(*i)++;
	start = *i;
	while (str[*i] != '\'' && str[*i] != '\0')
		(*i)++;
	enqueue(&shell->exp_front, &shell->exp_rear, \
	shell_substr(shell, str, start, (*i - start)));
	if (str[*i] == '\'')
		(*i)++;
}

void	d_quote_last(t_shell *shell, char *str, int *i)
{
	int	start;

	(*i)++;
	start = *i;
	if (str[*i] == '\"')
		enqueue(&shell->exp_front, &shell->exp_rear, \
		shell_substr(shell, str, start, *i - start));
	while (str[*i] != '\"' && str[*i] != '\0')
		(*i)++;
	if (*i != start)
		enqueue(&shell->exp_front, &shell->exp_rear, \
		shell_substr(shell, str, start, *i - start));
	if (str[*i] == '\"')
		(*i)++;
}

void	non_quote_last(t_shell *shell, char *str, int *i)
{
	int	start;

	start = *i;
	while(str[*i] != '\"' && str[*i] != '\'' && str[*i] != '\0')
		(*i)++;
	if (*i != start)
		enqueue(&shell->exp_front, &shell->exp_rear, \
		shell_substr(shell, str, start, *i - start));
}

void	delete_quotes(t_shell *shell)
{
	t_token	*temp_token;
	int		*i;
	int		j;
	int		k;

	temp_token = shell->token;
	j = 0;
	i = &j;
	while (temp_token)
	{
		if (temp_token->type == 4 && (ft_strchr(temp_token->str, '\'') || ft_strchr(temp_token->str, '\"')))
			temp_token->type = 9;
		j = 0;
		while (temp_token->str && temp_token->str[*i])
		{
			if (temp_token->str[*i] == '\'')
				s_quote_last(shell, temp_token->str, i);
			else if (temp_token->str[*i] == '\"')
				d_quote_last(shell, temp_token->str, i);
			else
				non_quote_last(shell, temp_token->str, i);
		}
		merge_queue(shell, temp_token);
		temp_token = temp_token->next;
	}
}
