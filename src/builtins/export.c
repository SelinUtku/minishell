/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 03:37:42 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/12 06:15:35 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_env_var(t_shell *shell, char *var, char *value)
{
	int		index;
	char	*temp;

	index = ft_getenv(shell->my_env, var);
	if (index != -1)
	{
		temp = shell->my_env[index];
		shell->my_env[index] = shell_strjoin(shell, var, "=");
		// del_one_from_garbage(&shell->garbage, temp);
		temp = shell->my_env[index];
		shell->my_env[index] = shell_strjoin(shell, var, value);
		// del_one_from_garbage(&shell->garbage, temp);
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
	free_double_from_garbage(&shell->garbage, temp);
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
