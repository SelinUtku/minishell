/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_garbage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 04:43:29 by Cutku             #+#    #+#             */
/*   Updated: 2023/06/09 04:43:48 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_garbage(t_garbage **first, void *ptr)
{
	t_garbage	*new;
	t_garbage	*last;

	new = (t_garbage *)malloc(sizeof(t_garbage));
	if (!new)
	{
		perror("malloc fail");
		exit (EXIT_FAILURE);
	}
	new->ptr = ptr;
	new->next = NULL;
	if (*first == NULL)
		*first = new;
	else
	{
		last = *first;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}