/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 02:41:30 by Cutku             #+#    #+#             */
/*   Updated: 2023/06/29 05:27:47 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	s_quote_expand(t_shell *shell, t_queue_exp **temp_front, t_queue_exp **temp_rear, char *str, int *i)// no expand
{
	int		start;

	start = *i;
	while (str[*i] != '\'' && str[*i] != '\0')
		(*i)++;
	exp_enqueue(temp_front, temp_rear, ft_substr(str, start, (*i - start)));
	if (str[*i] == '\'')
		(*i)++;
}

void dollar_func(t_shell *shell, t_queue_exp **temp_front, t_queue_exp **temp_rear, char *str, int *i)
{
	char	*var;
	char	*value;
	int		start;

	(*i)++;
	start = *i;
	if (str[*i] == '\0' || str[*i] == '\"')
	{
		var = ft_strdup("$");
		exp_enqueue(temp_front, temp_rear, var);
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
	exp_enqueue(temp_front, temp_rear, value);
	free(var);
}

void	d_quote_expand(t_shell *shell, t_queue_exp **temp_front, t_queue_exp **temp_rear, char *str, int *i)
{
	int		start;

	start = *i;
	while (str[*i] != '\"' && str[*i] != '\0')
	{
		if (str[*i] == '$')
		{
			if (*i != start)
				exp_enqueue(temp_front, temp_rear, ft_substr(str, start, *i - start));
			dollar_func(shell, temp_front, temp_rear, str, i);
			start = *i;
			(*i)--;
		}
		(*i)++;
	}
	if (*i - start != 0)
	{
		if (str[*i] == '\"')
		{
			exp_enqueue(temp_front, temp_rear, ft_substr(str, start, *i - start));
			(*i)++;
		}
	}
}

void	non_quote_expand(t_shell *shell, t_queue_exp **temp_front, t_queue_exp **temp_rear, char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] != '\"' && str[*i] != '\'' && str[*i] != '\0')
	{
		if (str[*i] == '$')
		{
			if (*i != start)
				exp_enqueue(temp_front, temp_rear, ft_substr(str, start, *i - start));
			dollar_func(shell, temp_front, temp_rear, str, i);
			return ;
		}
		(*i)++;
	}
	if (*i != start)
		exp_enqueue(temp_front, temp_rear, ft_substr(str, start, *i - start));
}

void	is_expandable(t_shell *shell)
{
	t_queue_exp	*temp_front;
	t_queue_exp	*temp_rear;
	t_token		*temp_token;
	char		*new;
	int			*i;
	int			j;

	temp_token = shell->token;
	j = 0;
	i = &j;
	while (temp_token)
	{
		j = 0;
		while (temp_token->str && temp_token->str[*i])
		{
			if (temp_token->str[*i] == '\'')
			{
				(*i)++;
				s_quote_expand(shell, &temp_front, &temp_rear, temp_token->str, i);
			}
			else if (temp_token->str[*i] == '\"')
			{
				(*i)++;
				d_quote_expand(shell ,&temp_front, &temp_rear, temp_token->str, i);
			}
			else
				non_quote_expand(shell ,&temp_front, &temp_rear, temp_token->str, i);
		}
		t_queue_exp	*temp;

		temp = temp_front;
		// printf("EXPANSION\n");
		// while (temp && temp->str)
		// {
		// 	printf("String : %s--\n", temp->str);
		// 	temp = temp->next;
		// }
		new = temp_token->str;
		temp_token->str = merge_queue(shell, &temp_front, &temp_rear);
		free(new);
		temp_token = temp_token->next;
	}

}
