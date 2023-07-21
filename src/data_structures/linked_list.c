/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 06:44:28 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/20 22:45:54 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_token_node(t_shell *shell, t_type type, char *str)
{
	t_token	*new;
	t_token	*last;

	new = my_malloc(&shell->garbage, 1, sizeof(t_token));
	new->type = type;
	new->str = str;
	if (shell->token == NULL)
	{
		new->next = NULL;
		shell->token = new;
	}
	else
	{
		last = shell->token;
		while (last->next != NULL)
			last = last->next;
		new->next = NULL;
		last->next = new;
	}
}

void	add_token_next(t_shell *shell, t_token *token, t_type type, char *str)
{
	t_token	*new;
	t_token	*temp;

	new = my_malloc(&shell->garbage, 1, sizeof(t_token));
	new->type = type;
	new->str = str;
	temp = token->next;
	token->next = new;
	new->next = temp;
}
