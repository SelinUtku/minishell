/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_operations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 06:43:55 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/22 20:47:02 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_env(t_shell *shell, char **env)
{
	int	i;
	int	j;
	int	index_var;

	i = ft_double_strlen(env);
	index_var = ft_getenv(env, "OLDPWD");
	if (index_var != -1)
		i--;
	shell->my_env = my_malloc(&shell->garbage, (i + 1), sizeof(char *));
	i = 0;
	j = 0;
	while (env && env[i])
	{
		if (i != index_var)
			shell->my_env[j++] = shell_strdup(shell, env[i]);
		i++;
	}
	shell->my_env[j] = NULL;
}

void	add_env_var(t_shell *shell, char *var, char *value)
{
	char	**temp;
	int		i;
	int		len;

	temp = shell->my_env;
	len = ft_double_strlen(temp);
	shell->my_env = my_malloc(&shell->garbage, len + 2, sizeof(char *));
	i = 0;
	while (temp && temp[i])
	{
		shell->my_env[i] = temp[i];
		i++;
	}
	shell->my_env[i] = shell_strjoin(shell, var, value);
	shell->my_env[i + 1] = NULL;
	del_one_from_garbage(&shell->garbage, var);
	del_one_from_garbage(&shell->garbage, value);
	del_one_from_garbage(&shell->garbage, temp);
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
		del_one_from_garbage(&shell->garbage, var);
		del_one_from_garbage(&shell->garbage, value);
		del_one_from_garbage(&shell->garbage, temp);
	}
}

void	append_env_var(t_shell *shell, char *var, char *value)
{
	int		index;
	char	*temp;

	index = ft_getenv(shell->my_env, var);
	if (index != -1)
	{
		temp = shell->my_env[index];
		shell->my_env[index] = shell_strjoin(shell, temp, value);
		del_one_from_garbage(&shell->garbage, temp);
		del_one_from_garbage(&shell->garbage, var);
		del_one_from_garbage(&shell->garbage, value);
	}
}

void	delete_env_var(t_shell *shell, char *var)
{
	int		i;
	int		j;
	int		index_var;
	char	**temp;

	temp = shell->my_env;
	i = ft_double_strlen(temp);
	index_var = ft_getenv(temp, var);
	del_one_from_export(shell, var);
	if (index_var != -1)
	{
		shell->my_env = my_malloc(&shell->garbage, i, sizeof(char *));
		i = 0;
		j = 0;
		while (temp && temp[i])
		{
			if (i != index_var)
				shell->my_env[j++] = temp[i];
			i++;
		}
		shell->my_env[j] = NULL;
		del_one_from_garbage(&shell->garbage, temp[index_var]);
		del_one_from_garbage(&shell->garbage, temp);
	}
}
