/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 02:41:30 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/14 03:15:46 by Cutku            ###   ########.fr       */
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
	enqueue(&shell->exp_front, &shell->exp_rear, \
	shell_substr(shell, str, start, (*i - start)));
	if (str[*i] == '\'')
		(*i)++;
}

void	dollar_func(t_shell *shell, char *str, int *i)
{
	char	*var;
	int		start;

	(*i)++;
	start = *i;
	if (str[*i] == '?')
	{
		enqueue(&shell->exp_front, &shell->exp_rear, shell_strdup(shell, ft_itoa(shell->status)));
		(*i)++;
		return ;
	}
	if (str[*i] == '_' || ft_isalpha(str[*i]) == 1)
	{
		while (ft_isalnum(str[*i]) == 1 || str[*i] == '_')
			(*i)++;
		var = shell_substr(shell, str, start, *i - start);
		if (ft_getenv(shell->my_env, var) == -1)
		{
			// free(var); del one
			return ;
		}
		enqueue(&shell->exp_front, &shell->exp_rear, \
		value_of_expandable(shell, var));
		// free(var);// del one
		return ;
	}
	enqueue(&shell->exp_front, &shell->exp_rear, shell_strdup(shell, "$"));
	return ;
}

void	d_quote_expand(t_shell *shell, char *str, int *i, t_type type)
{
	int	start;

	(*i)++;
	start = *i;
	if (str[*i] == '\"')
		enqueue(&shell->exp_front, &shell->exp_rear, \
		shell_substr(shell, str, start, *i - start));
	while (str[*i] != '\"' && str[*i] != '\0')
	{
		if (str[*i] == '$' && type != 9 && type != 4)
		{
			if (*i != start)
				enqueue(&shell->exp_front, &shell->exp_rear, \
				shell_substr(shell, str, start, *i - start));
			dollar_func(shell, str, i);
			start = *i;
			(*i)--;
		}
		(*i)++;
	}
	if (*i != start)
		enqueue(&shell->exp_front, &shell->exp_rear, \
		shell_substr(shell, str, start, *i - start));
	if (str[*i] == '\"')
		(*i)++;
}

void	non_quote_expand(t_shell *shell, char *str, int *i, t_type type)
{
	int	start;

	start = *i;
	while (str[*i] != '\"' && str[*i] != '\'' && str[*i] != '\0')
	{
		if (str[*i] == '$' && type != 9 && type != 4)
		{
			if (*i != start)
				enqueue(&shell->exp_front, &shell->exp_rear, \
				shell_substr(shell, str, start, *i - start));
			dollar_func(shell, str, i);
			return ;
		}
		(*i)++;
	}
	if (*i != start)
		enqueue(&shell->exp_front, &shell->exp_rear, \
		shell_substr(shell, str, start, *i - start));
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
		if (temp_token->type == 4 && (ft_strchr(temp_token->str, '\'') || ft_strchr(temp_token->str, '\"')))
			temp_token->type = 9;
			j = 0;
			while (temp_token->str && temp_token->str[*i])
			{
				if (temp_token->str[*i] == '\'')
					s_quote_expand(shell, temp_token->str, i);
				else if (temp_token->str[*i] == '\"')
					d_quote_expand(shell, temp_token->str, i, temp_token->type);
				else
					non_quote_expand(shell, temp_token->str, i, temp_token->type);
			}
			merge_queue(shell, temp_token);
		temp_token = temp_token->next;
	}
}
