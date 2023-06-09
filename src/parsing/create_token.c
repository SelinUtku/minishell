/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_ll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 03:53:57 by sutku             #+#    #+#             */
/*   Updated: 2023/06/09 04:41:51 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_token_node(t_token **token, t_type type, int index, char *str)
{
	t_token	*new;
	t_token	*last;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->type = type;
	new->index = index;
	new->str = str;
	if (*token == NULL)
	{
		new->prev = NULL;
		new->next = NULL;
		*token = new;
	}
	else
	{
		last = *token;
		while (last->next != NULL)
			last = last->next;
		new->prev = last;
		new->next = NULL;
		last->next = new;
	}
}
