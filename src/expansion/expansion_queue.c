/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:51:44 by Cutku             #+#    #+#             */
/*   Updated: 2023/06/28 16:11:17 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exp_enqueue(t_queue_exp **front, t_queue_exp **rear, char *ptr)
{
	t_queue_exp	*new;

	new = NULL;
	new = (t_queue_exp *)malloc(sizeof(t_queue_exp));
	if (!new)
	{
		perror ("malloc");
		exit (EXIT_FAILURE);
	}
	new->str = ptr;
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

void	exp_dequeue(t_queue_exp **front)
{
	t_queue_exp	*temp;

	if (*front != NULL)
	{
		temp = *front;
		*front = (*front)->next;
		free(temp);
	}
	else
		ft_putstr_fd("Queue is empty.\n", 2);
}