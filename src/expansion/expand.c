/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 02:41:30 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/05 00:00:59 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	s_quote_expand(t_shell *shell, char *str, int *i)
{
	int		start;

	(*i)++;
	start = *i;
	while (str[*i] != '\'' && str[*i] != '\0')
		(*i)++;
	enqueue(&shell->exp_front, &shell->exp_rear, ft_substr(str, start, (*i - start)));
	if (str[*i] == '\'')
		(*i)++;
}

void	dollar_func(t_shell *shell, char *str, int *i)
{
	char	*var;
	char	*value;
	int		start;

	(*i)++;
	start = *i;
	if (str[*i] == '\0' || str[*i] == '\"')
	{
		var = ft_strdup("$");
		enqueue(&shell->exp_front, &shell->exp_rear, var);
		return ;
	}
	else if (ft_isdigit(str[*i]) == 1)
	{
		(*i)++;
		return ;
	}
	while (ft_isalnum(str[*i]) == 1 || str[*i] == '_')
		(*i)++;
	var = ft_substr(str, start, *i - start);
	if (ft_getenv(shell->my_env, var) == -1)
	{
		free(var);
		return ;
	}
	value = value_of_expandable(shell, var);
	enqueue(&shell->exp_front, &shell->exp_rear, value);
	free(var);
}

void	d_quote_expand(t_shell *shell, char *str, int *i)
{
	int		start;

	(*i)++;
	start = *i;
	while (str[*i] != '\"' && str[*i] != '\0')
	{
		if (str[*i] == '$')
		{
			if (*i != start)
				enqueue(&shell->exp_front, &shell->exp_rear, ft_substr(str, start, *i - start));
			dollar_func(shell, str, i);
			start = *i;
			(*i)--;
		}
		(*i)++;
	}
	if (*i - start != 0)
	{
		if (str[*i] == '\"')
		{
			enqueue(&shell->exp_front, &shell->exp_rear, ft_substr(str, start, *i - start));
			(*i)++;
		}
	}
}

void	non_quote_expand(t_shell *shell, char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] != '\"' && str[*i] != '\'' && str[*i] != '\0')
	{
		if (str[*i] == '$')
		{
			if (*i != start)
				enqueue(&shell->exp_front, &shell->exp_rear, ft_substr(str, start, *i - start));
			dollar_func(shell, str, i);
			return ;
		}
		(*i)++;
	}
	if (*i != start)
		enqueue(&shell->exp_front, &shell->exp_rear, ft_substr(str, start, *i - start));
}

void	is_expandable(t_shell *shell)
{
	t_token	*temp_token;
	int		*i;
	int		j;

	temp_token = shell->token;
	j = 0;
	i = &j;
	while (temp_token)
	{
		j = 0;
		while (temp_token->str && temp_token->str[*i])
		{
			if (temp_token->str[*i] == '\'')
				s_quote_expand(shell, temp_token->str, i);
			else if (temp_token->str[*i] == '\"')
				d_quote_expand(shell, temp_token->str, i);
			else
				non_quote_expand(shell, temp_token->str, i);
		}
		merge_queue(shell, temp_token);
		temp_token = temp_token->next;
	}
}
