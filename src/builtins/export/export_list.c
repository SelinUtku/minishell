/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 08:16:34 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/24 23:11:07 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	create_export_list(t_shell *shell)
{
	int		i;
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

void	print_export_list(t_shell *shell)
{
	t_export	*temp;

	temp = shell->export_list;
	while (temp)
	{
		ft_putstr_fd("declare - x ", 1);
		ft_putstr_fd(temp->key, 1);
		if (temp->value)
		{
			ft_putchar_fd('=', 1);
			ft_putchar_fd('\"', 1);
			ft_putstr_fd(temp->value, 1);
			ft_putchar_fd('\"', 1);
		}
		ft_putchar_fd('\n', 1);
		temp = temp->next;
	}
}
