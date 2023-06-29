/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 03:25:09 by Cutku             #+#    #+#             */
/*   Updated: 2023/06/26 01:38:39 by Cutku            ###   ########.fr       */
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
	shell->my_env = malloc((i + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (env && env[i])
	{
		if (i != index_var)
			shell->my_env[j] = ft_strdup(env[i]);
		else
			j--;
		i++;
		j++;
	}
	shell->my_env[j] = NULL;
	// ft_env(shell);
}

int	ft_getenv(char **str, char *var)
{
	int	i;

	i = 0;
	while (str && var && str[i])
	{
		if (ft_strncmp(str[i], var, ft_strlen(var)) == 0)
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
			str = ft_strdup(&str[ft_strlen(var) + 1]);
			return (str);
		}
	}
	return (NULL);
}

void	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->my_env != NULL && shell->my_env[i] != NULL)
	{
		printf("%s\n", shell->my_env[i]);
		i++;
	}
}