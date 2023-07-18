/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 03:25:05 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/18 09:41:57 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	count_words(char *str)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (str && str[i] != '\0')
	{
		while (str && ft_strchr(IFS, str[i]))
			i++;
		if (str[i] != '\0')
			counter++;
		while (ft_strchr(IFS, str[i]) == 0 && str[i] != '\0')
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

void	s_quote_expand(t_shell *shell, char *str, int *i)
{
	int		start;

	start = *i;
	(*i)++;
	while (str[*i] != '\'' && str[*i] != '\0')
		(*i)++;
	if (str[*i] == '\'')
		(*i)++;
	enqueue(&shell->exp_front, &shell->exp_rear, \
	shell_substr(shell, str, start, (*i - start)));
}

void	d_quote_expand(t_shell *shell, char *str, int *i, t_type *type)
{
	int	start;

	start = *i;
	(*i)++;
	if (str[*i] == '\"')
		enqueue(&shell->exp_front, &shell->exp_rear, \
		shell_substr(shell, str, start, *i - start + 1));
	while (str[*i] != '\"' && str[*i] != '\0')
	{
		if (str[*i] == '$' && *type != 9 && *type != 4)
		{
			enqueue(&shell->exp_front, &shell->exp_rear, \
			shell_substr(shell, str, start, *i - start));
			dollar_func(shell, str, i);
			start = *i;
			(*i)--;
		}
		(*i)++;
	}
	if (str[*i] == '\"')
		(*i)++;
		enqueue(&shell->exp_front, &shell->exp_rear, \
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
		// if (*type == 5 && check_for_file_name(value_of_expandable(shell, var)) > 1)
		// {
		// 	*type = AMBIGIOUS_R;
		// 	enqueue(&shell->exp_front, &shell->exp_rear, shell_strdup(shell, "$"));
		// 	enqueue(&shell->exp_front, &shell->exp_rear, var);
		// 	return ;
		// }
		enqueue(&shell->exp_front, &shell->exp_rear, \
		value_of_expandable(shell, var));
		// free(var);// del one
		return ;
	}
	enqueue(&shell->exp_front, &shell->exp_rear, shell_strdup(shell, "$"));
	return ;
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
		if (temp_token->type == DELIMITER && (ft_strchr(temp_token->str, '\'') || ft_strchr(temp_token->str, '\"')))
			temp_token->type = Q_DELIMITER;
		if (temp_token->type != DELIMITER && temp_token->type != Q_DELIMITER)
		{
			j = 0;
			while (temp_token->str && temp_token->str[*i])
			{
				if (temp_token->str[*i] == '\'')
					s_quote_expand(shell, temp_token->str, i);
				else if (temp_token->str[*i] == '\"')
					d_quote_expand(shell, temp_token->str, i, &temp_token->type);
				else
					non_quote_expand(shell, temp_token->str, i, &temp_token->type);
			}
			merge_queue(shell, temp_token);
		}
		temp_token = temp_token->next;
	}
}

// void	ft_isspace(t_shell *shell)
// {
// 	while (shell->input[shell->i] == ' ' && shell->input[shell->i] != '\0')
// 		shell->i++;
// }

void	split_after_expand(t_shell *shell)
{
	int		start;
	int		i;
	int		j;
	char	*str;
	t_token	*temp_token;

	temp_token = shell->token;
	while (temp_token)
	{
		if (count_words(temp_token->str) > 1)
		{
			str = temp_token->str;
			i = 0;
			j = 0;
			while (str && str[i] != '\0')
			{
				while (str && ft_strchr(IFS, str[i]))
					i++;
				start = i;
				while (ft_strchr(IFS, str[i]) == 0 && str[i] != '\0')
				{
					if (str[i] == '\'')
						single_quote_state(str, &i);
					else if (str[i] == '\"')
						double_quote_state(str, &i);
					else
						i++;
				}
				if (j == 0)
				{
					temp_token->str = shell_substr(shell, str, start, i - start);//free lazim
					j++;
				}
				else
				{
					add_token_next(shell, temp_token, temp_token->type, \
					shell_substr(shell, str, start, i - start));
					temp_token = temp_token->next;
				}

			}
		}
		temp_token = temp_token->next;
	}
}


