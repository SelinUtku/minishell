/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 08:16:34 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/22 22:45:38 by Cutku            ###   ########.fr       */
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

void	create_export_list(t_shell *shell)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (shell->my_env && shell->my_env[i])
	{
		temp = ft_strchr(shell->my_env[i], '=');
		add_to_export(shell, shell_substr(shell, shell->my_env[i], 0, \
		temp - shell->my_env[i]), shell_strdup(shell, temp + 1));
		i++;
	}
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

t_export	*check_export_list(t_shell *shell, char *key)
{
	t_export	*temp;

	temp = shell->export_list;
	while (temp && temp->key)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
