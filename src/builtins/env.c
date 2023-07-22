/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 03:25:09 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/22 06:48:04 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		ft_putendl_fd(shell->my_env[i], 1);
		i++;
	}
	shell->status = 0;
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
