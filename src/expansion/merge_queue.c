/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 04:15:51 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/04 23:09:35 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	merge_queue(t_shell *shell, t_token *token)
{
	char		*temp;

	temp = NULL;
	if (shell->exp_front)
	{
		temp = ft_strdup((shell->exp_front->content));
		dequeue(&shell->exp_front);
	}
	while (shell->exp_front)
	{
		temp = ft_strjoin(temp, shell->exp_front->content);
		dequeue(&shell->exp_front);
	}
	token->str = temp;
}
