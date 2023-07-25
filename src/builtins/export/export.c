/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 03:37:42 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/25 20:59:18 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_export(t_shell *shell, char **str)
{
	int		i;

	g_exit_status = 0;
	if (!str[1])
		return (print_export_list(shell));
	if (str[1][0] == '-' && str[1][1])
		return (error_invalid_option(str));
	i = 1;
	while (str[i])
	{
		export_operations(shell, str, i);
		i++;
	}
}

void	export_operations(t_shell *shell, char **str, int i)
{
	int		append;
	int		j;
	char	*key;

	append = 0;
	j = is_valid_syntax_var(str[i]);
	if (j && str[i][j] == '+' && str[i][j + 1] == '=')
	{
		append = -1;
		j++;
	}
	if (j && (str[i][j] == '=' || str[i][j] == '\0'))
	{
		key = shell_substr(shell, str[i], 0, j + append);
		if (str[i][j] == '=')
		{
			export_to_exp_list(shell, str[i] + j, append, key);
			key = shell_substr(shell, str[i], 0, j + append);
			export_to_env(shell, str[i] + j, append, key);
		}
		else if (check_export_list(shell, key) == NULL)
			add_to_export(shell, shell_substr(shell, str[i], 0, j), NULL);
	}
	else
		error_not_valid_identifier(str[0], str[i]);
}

void	export_to_exp_list(t_shell *shell, char *str, int append, char *key)
{
	if (check_export_list(shell, key))
	{
		if (append == 0)
			update_export_list(shell, key, shell_strdup(shell, str + 1));
		else
			append_to_export(shell, key, shell_strdup(shell, str + 1));
	}
	else
		add_to_export(shell, key, shell_strdup(shell, str + 1));
}

void	export_to_env(t_shell *shell, char *str, int append, char *key)
{
	if (ft_getenv(shell->my_env, key) == -1)
		add_env_var(shell, key, shell_strdup(shell, str));
	else
	{
		if (append == 0)
			update_env_var(shell, key, shell_strdup(shell, str));
		else
			append_env_var(shell, key, shell_strdup(shell, str + 1));
	}
}
