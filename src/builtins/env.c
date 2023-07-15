/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 03:25:09 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/15 01:59:06 by Cutku            ###   ########.fr       */
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
			shell->my_env[j] = shell_strdup(shell, env[i]);
		else
			j--;
		i++;
		j++;
	}
	shell->my_env[j] = NULL;
}

int	ft_getenv(char **str, char *var)
{
	int	i;
	int	custom;

	i = 0;
	custom = 0;
	if (var && var[ft_strlen(var) - 1] == '=')
		custom = 1;
	while (str && var && str[i])
	{
		if (ft_strncmp(str[i], var, ft_strlen(var)) == 0 && \
		(ft_strchr(str[i], '=') - str[i]) == ft_strlen(var) - custom)
			return (i);
		i++;
	}
	return (-1);
}

char	*value_of_expandable(t_shell *shell, char *var)
{
	char	*str;
	int		i;

	i = ft_getenv(shell->my_env, var);
	if (i != -1)
	{
		str = shell->my_env[i];
		if (str)
		{
			str = shell_strdup(shell, &str[ft_strlen(var) + 1]);
			return (str);
		}
	}
	return (NULL);
}

void	ft_env(t_shell *shell, char **str)
{
	int	i;

	if (ft_double_strlen(str) > 1)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(str[1], 2);
		ft_putendl_fd(": env no argument or no options", 2);
		shell->status = 1;
		return ;
	}
	i = 0;
	while (shell->my_env != NULL && shell->my_env[i] != NULL)
	{
		printf("%s\n", shell->my_env[i]);
		i++;
	}
	shell->status = 0;
}
