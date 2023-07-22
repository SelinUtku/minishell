/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 03:37:42 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/22 09:22:30 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_export(t_shell *shell, char **str)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	shell->status = 0;
	if (!str[1])
		return (print_export_list(shell));
	if (str[1][0] == '-')
		return (error_invalid_option(shell, str));
	i = 1;
	while (str[i])
	{
		j = is_valid_syntax_var(shell, str[i]);
		if (j && (str[i][j] == '=' || str[i][j] == '\0'))
		{
			key = shell_substr(shell, str[i], 0, j);
			if (str[i][j] == '=')
			{
				value = shell_strdup(shell, str[i] + j + 1);
				if (check_export_list(shell, key))
					update_export_list(shell, key, value);
				else
					add_list(shell, key, value);
				key = shell_substr(shell, str[i], 0, j);
				if (ft_getenv(shell->my_env, key) == -1)
					add_env_var(shell, key, shell_strdup(shell, str[i] + j));
				else
					update_env_var(shell, key, shell_strdup(shell, str[i] + j));
			}
			else if (check_export_list(shell, key) == false)
				add_list(shell, shell_substr(shell, str[i], 0, j), NULL);
		}
		else
			error_not_valid_identifier(shell, str[0], str[i]);
		i++;
	}
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