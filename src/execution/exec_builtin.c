/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:29:53 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/10 02:42:06 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	is_builtin(t_token *token)
{
	int	i;

	while (token && token->type != PIPE)
	{
		if (token->type = WORD)
		{
			ft_strncmp
		}
	}
}