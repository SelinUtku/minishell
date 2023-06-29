/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 04:15:51 by Cutku             #+#    #+#             */
/*   Updated: 2023/06/29 05:24:39 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*merge_queue(t_shell *shell, t_queue_exp **temp_front, t_queue_exp **temp_rear)
{
	char		*temp;

	temp = NULL;
	if (temp_front && *temp_front)
	{
		temp = ft_strdup((*temp_front)->str);
		exp_dequeue(temp_front);
	}
	while (temp_front && *temp_front)
	{
		temp = ft_strjoin(temp, (*temp_front)->str);
		exp_dequeue(temp_front);
	}
	return (temp);
}
