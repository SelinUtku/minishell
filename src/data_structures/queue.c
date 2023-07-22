/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:47:24 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/22 04:45:44 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	enqueue(t_shell *shell, t_queue **front, t_queue **rear, void *ptr)
{
	t_queue	*new;

	new = NULL;
	new = (t_queue *)my_malloc(&shell->garbage, 1, sizeof(t_queue));
	new->content = ptr;
	new->next = NULL;
	if (*front == NULL)
	{
		*front = new;
		*rear = new;
	}
	else
	{
		(*rear)->next = new;
		*rear = new;
	}
}

void	dequeue(t_shell *shell, t_queue **front)
{
	t_queue	*temp;

	if (*front != NULL)
	{
		temp = *front;
		*front = (*front)->next;
		del_one_from_garbage(&shell->garbage, temp->content);
		del_one_from_garbage(&shell->garbage, temp);
	}
	else
		ft_putstr_fd("Queue is empty.\n", 2);
}
