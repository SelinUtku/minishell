/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_states.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 04:22:04 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/21 08:26:24 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	s_quote_expand(t_shell *shell, char *str, int *i)
{
	int		start;

	start = *i;
	single_quote_state(str, i);
	enqueue(shell, &shell->exp_front, &shell->exp_rear, \
	shell_substr(shell, str, start, (*i - start)));
}

void	d_quote_expand(t_shell *shell, char *str, int *i, t_type *type)
{
	int	start;

	start = *i;
	(*i)++;
	if (str[*i] == '\"')
		enqueue(shell, &shell->exp_front, &shell->exp_rear, \
		shell_substr(shell, str, start, *i - start + 1));
	while (str[*i] != '\"' && str[*i] != '\0')
	{
		if (str[*i] == '$' && *type != 9 && *type != 4)
		{
			enqueue(shell, &shell->exp_front, &shell->exp_rear, \
			shell_substr(shell, str, start, *i - start));
			if_dollar_sign(shell, str, i);
			start = *i;
			(*i)--;
		}
		(*i)++;
	}
	if (str[*i] == '\"')
		(*i)++;
	enqueue(shell, &shell->exp_front, &shell->exp_rear, \
	shell_substr(shell, str, start, *i - start));
}

void	non_quote_expand(t_shell *shell, char *str, int *i, t_type *type)
{
	int	start;

	start = *i;
	while (str[*i] != '\"' && str[*i] != '\'' && str[*i] != '\0')
	{
		if (str[*i] == '$' && *type != 9 && *type != 4)
		{
			if (*i != start)
				enqueue(shell, &shell->exp_front, &shell->exp_rear, \
				shell_substr(shell, str, start, *i - start));
			if (str[*i + 1] == '\"' || str[*i + 1] == '\'')
			{
				(*i)++;
				return ;
			}
			if_dollar_sign(shell, str, i);
			return ;
		}
		(*i)++;
	}
	if (*i != start)
		enqueue(shell, &shell->exp_front, &shell->exp_rear, \
		shell_substr(shell, str, start, *i - start));
}
