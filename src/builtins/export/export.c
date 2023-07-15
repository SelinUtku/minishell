/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 03:37:42 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/14 16:58:33 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_export(t_shell *shell, char **str)
{
	int		i;
	int		j;
	int		flag;
	char	*key;

	shell->status = 0;
	if (!str[1])
		return (print_export_list(shell));
	if (str[1][0] == '-')
		return (error_invalid_option(shell, str));
	if (str[1][0] == '\0' || str[1][0] == '=')
		return (error_not_valid_identifier(shell, str[0], str[i]));
	i = 1;
	while (str[i])
	{
		j = 0;
		flag = 1;
		while (str[i][j] != '\0' && str[i][j] != '=' && flag)
		{
			if (ft_isalpha(str[i][0]) == 0 && str[i][0] != '_')
			{
				error_not_valid_identifier(shell, str[0], str[i]);
				flag = 0 ;
			}
			else if (ft_isalnum(str[i][j]) == 0 && str[i][j] != '_')
			{
				error_not_valid_identifier(shell, str[0], str[i]);
				flag = 0;
			}
			j++;
		}
		if (flag)
		{
			if (str[i][j] == '=')
			{
				key = shell_substr(shell, str[i], 0, j);
				if (check_list(shell, key, shell_strdup(shell, str[i] + j + 1)))
					add_list(shell, key, shell_strdup(shell, str[i] + j + 1));
				if (ft_getenv(shell->my_env, key) == -1)
					add_env_var(shell, key, shell_strdup(shell, str[i] + j));
				else
					update_env_var(shell, key, shell_strdup(shell, str[i] + j));
			}
			else
				add_list(shell, shell_substr(shell, str[i], 0, j), NULL);
		}
		i++;
	}
}

void	update_env_var(t_shell *shell, char *var, char *value)
{
	int		index;
	char	*temp;

	index = ft_getenv(shell->my_env, var);
	if (index != -1)
	{
		temp = shell->my_env[index];
		shell->my_env[index] = shell_strjoin(shell, var, value);
		del_one_from_garbage(&shell->garbage, temp);
	}
}

void	append_env_var(t_shell *shell, char *var, char *value)//export +=
{
	int		index;
	char	*temp;

	index = ft_getenv(shell->my_env, var);
	if (index != -1)
	{
		temp = shell->my_env[index];
		shell->my_env[index] = shell_strjoin(shell, shell->my_env[index], value);
		del_one_from_garbage(&shell->garbage, temp);
	}
}

void	add_env_var(t_shell *shell, char *var, char *value)//export
{
	char	**temp;
	int		i;

	temp = shell->my_env;
	shell->my_env = my_malloc(&shell->garbage, \
	(ft_double_strlen(temp) + 2), sizeof(char *));
	i = 0;
	while (temp && temp[i])
	{
		shell->my_env[i] = temp[i];
		i++;
	}
	shell->my_env[i] = shell_strjoin(shell, var, value);
	shell->my_env[i + 1] = NULL;
	// free_double_from_garbage(&shell->garbage, temp); leak var.
	// free(temp); // del one double pointer
}

void	free_double_from_garbage(t_garbage **garbage, char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		del_one_from_garbage(garbage, ptr[i]);
		i++;
	}
	del_one_from_garbage(garbage, ptr);//?
}
