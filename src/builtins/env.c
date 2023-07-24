/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 03:25:09 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/24 21:25:54 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_shell *shell, char **str)
{
	int	i;

	if (ft_double_strlen(str) > 1)
	{
		if (str[1][0] == '-')
		{
			error_printer("env: ", "illegal option -- ", str[1]);
			shell->status = 1;
		}
		else
		{
			error_printer("env: ", str[1], NO_FILE);
			shell->status = 127;
		}
		return ;
	}
	i = 0;
	while (shell->my_env != NULL && shell->my_env[i] != NULL)
	{
		ft_putendl_fd(shell->my_env[i], STDOUT_FILENO);
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
