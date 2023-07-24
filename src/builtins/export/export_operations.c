/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:30:27 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/23 17:33:41 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	add_to_export(t_shell *shell, char *key, char *value)
{
	t_export	*new;
	t_export	*last;

	new = (t_export *)my_malloc(&shell->garbage, 1, sizeof(t_export));
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (shell->export_list == NULL)
		shell->export_list = new;
	else
	{
		last = shell->export_list;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

void	append_to_export(t_shell *shell, char *key, char *value)
{
	t_export	*temp;
	char		*str;

	temp = check_export_list(shell, key);
	str = temp->value;
	temp->value = shell_strjoin(shell, str, value);
	del_one_from_garbage(&shell->garbage, str);
	del_one_from_garbage(&shell->garbage, key);
	del_one_from_garbage(&shell->garbage, value);
}

void	update_export_list(t_shell *shell, char *key, char *value)
{
	t_export	*temp;

	temp = shell->export_list;
	while (temp && temp->key)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			if (temp->value != NULL)
				del_one_from_garbage(&shell->garbage, temp->value);
			temp->value = value ;
			del_one_from_garbage(&shell->garbage, key);
			return ;
		}
		temp = temp->next;
	}
}

void	del_one_from_export(t_shell *shell, char *key)
{
	t_export	*prev;
	t_export	*del;

	del = shell->export_list;
	prev = NULL;
	if (del && ft_strcmp(shell->export_list->key, key) == 0)
	{
		shell->export_list = shell->export_list->next;
		del_node_from_export(shell, del);
	}
	else
	{
		while (del != NULL)
		{
			if (ft_strcmp(del->key, key) == 0)
			{
				prev->next = del->next;
				del_node_from_export(shell, del);
				break ;
			}
			prev = del;
			del = del->next;
		}
	}
}

void	del_node_from_export(t_shell *shell, t_export *del)
{
	del_one_from_garbage(&shell->garbage, del->key);
	if (del->value)
		del_one_from_garbage(&shell->garbage, del->value);
	del_one_from_garbage(&shell->garbage, del);
}
