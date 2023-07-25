/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 03:25:05 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/25 20:46:23 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_code_expand(t_shell *shell, int *i)
{
	char	*var;

	var = ft_itoa(g_exit_status);
	enqueue(shell, &shell->exp_front, &shell->exp_rear, \
	shell_strdup(shell, var));
	free(var);
	(*i)++;
}

void	variable_expand(t_shell *shell, char *str, int *i, int len_variable)
{
	char	*var;

	var = shell_substr(shell, str, *i, len_variable);
	(*i) += len_variable;
	if (ft_getenv(shell->my_env, var) == -1)
	{
		del_one_from_garbage(&shell->garbage, var);
		return ;
	}
	enqueue(shell, &shell->exp_front, &shell->exp_rear, \
	value_of_expandable(shell, var));
	del_one_from_garbage(&shell->garbage, var);
	return ;
}

void	if_dollar_sign(t_shell *shell, char *str, int *i)
{
	int	len_variable;

	(*i)++;
	if (str[*i] == '?')
	{
		exit_code_expand(shell, i);
		return ;
	}
	len_variable = is_valid_syntax_var(&str[*i]);
	if (len_variable != 0)
	{
		variable_expand(shell, str, i, len_variable);
		return ;
	}
	enqueue(shell, &shell->exp_front, &shell->exp_rear, \
	shell_strdup(shell, "$"));
}

char	*value_of_expandable(t_shell *shell, char *var)
{
	char	*str;
	int		i;

	i = ft_getenv(shell->my_env, var);
	if (i != -1)
	{
		str = shell->my_env[i];
		if (str)
		{
			str = shell_strdup(shell, &str[ft_strlen(var) + 1]);
			return (str);
		}
	}
	return (NULL);
}

void	is_expandable(t_shell *shell)
{
	t_token	*token;
	int		i;

	token = shell->token;
	while (token)
	{
		if (token->type != DELIMITER && token->type != Q_DELIMITER)
		{
			i = 0;
			while (token->str && token->str[i])
			{
				if (token->str[i] == '\'')
					s_quote_expand(shell, token->str, &i);
				else if (token->str[i] == '\"')
					d_quote_expand(shell, token->str, &i, &token->type);
				else
					non_quote_expand(shell, token->str, &i, &token->type);
			}
			del_one_from_garbage(&shell->garbage, token->str);
			token->str = merge_queue(shell);
		}
		token = token->next;
	}
}
