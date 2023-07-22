/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_states.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 03:52:35 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/21 09:34:56 by Cutku            ###   ########.fr       */
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

void	skip_spaces(char *str, int *i)
{
	while (ft_isspace(str[*i]) && str[*i] != '\0')
		(*i)++;
}
