/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 04:15:51 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/24 23:11:33 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*merge_queue(t_shell *shell)
{
	char		*temp;
	char		*str;

	temp = NULL;
	str = NULL;
	if (shell->exp_front)
	{
		str = shell_strdup(shell, (shell->exp_front->content));
		del_one_from_garbage(&shell->garbage, shell->exp_front->content);
		dequeue(shell, &shell->exp_front);
	}
	while (shell->exp_front)
	{
		temp = str;
		str = shell_strjoin(shell, temp, shell->exp_front->content);
		del_one_from_garbage(&shell->garbage, temp);
		del_one_from_garbage(&shell->garbage, shell->exp_front->content);
		dequeue(shell, &shell->exp_front);
	}
	return (str);
}
