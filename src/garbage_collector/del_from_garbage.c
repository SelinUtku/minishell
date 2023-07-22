/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_from_garbage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 04:47:09 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/21 06:14:50 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	del_one_from_garbage(t_garbage **first, void *ptr)
{
	t_garbage	*prev;
	t_garbage	*del;

	del = *first;
	prev = NULL;
	if ((*first)->ptr == ptr)
	{
		*first = (*first)->next;
		del_node(del);
	}
	else
	{
		while (del != NULL)
		{
			if (del->ptr == ptr)
			{
				prev->next = del->next;
				del_node(del);
				break ;
			}
			prev = del;
			del = del->next;
		}
	}
}

void	clean_garbage(t_garbage **first)
{
	t_garbage	*del;

	while (*first != NULL)
	{
		del = *first;
		*first = (*first)->next;
		del_node(del);
	}
}

void	del_node(t_garbage *del)
{
	if (del->ptr)
		free(del->ptr);
	del->ptr = NULL;
	free(del);
	del = NULL;
}
