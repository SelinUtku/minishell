/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:47:24 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/13 02:58:01 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	enqueue(t_queue **front, t_queue **rear, void *ptr)
{
	t_queue	*new;

	new = NULL;
	new = (t_queue *)malloc(sizeof(t_queue));
	if (!new)
	{
		perror ("malloc");
		exit (EXIT_FAILURE);
	}
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

void	dequeue(t_queue **front)
{
	t_queue	*temp;

	if (*front != NULL)
	{
		temp = *front;
		*front = (*front)->next;
		free(temp);
	}
	else
		ft_putstr_fd("Queue is empty.\n", 2);
}