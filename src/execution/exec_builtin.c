/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:29:53 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/25 21:00:50 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *str)
{
	if (str)
	{
		if (!ft_strcmp(str, "echo"))
			return (1);
		else if (!ft_strcmp(str, "export"))
			return (2);
		else if (!ft_strcmp(str, "unset"))
			return (3);
		else if (!ft_strcmp(str, "exit"))
			return (4);
		else if (!ft_strcmp(str, "cd"))
			return (5);
		else if (!ft_strcmp(str, "env"))
			return (6);
		else if (!ft_strcmp(str, "pwd"))
			return (7);
		return (0);
	}
	return (0);
}

void	which_builtin(t_shell *shell, char **str)
{
	if (str)
	{
		if (!ft_strcmp(*str, "echo"))
			ft_echo(str);
		else if (!ft_strcmp(*str, "export"))
			ft_export(shell, str);
		else if (!ft_strcmp(*str, "unset"))
			ft_unset(shell, str);
		else if (!ft_strcmp(*str, "exit"))
			ft_exit(shell, str);
		else if (!ft_strcmp(*str, "cd"))
			ft_cd(shell, str[1]);
		else if (!ft_strcmp(*str, "env"))
			ft_env(shell, str);
		else if (!ft_strcmp(*str, "pwd"))
			ft_pwd(str);
	}
}

void	exec_builtin(t_shell *shell, char **str, t_pipex *pipex)
{
	which_builtin(shell, str);
	close_pipes(pipex);
	exit (0);
}
