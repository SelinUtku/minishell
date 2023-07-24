/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_messages.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 23:51:11 by sutku             #+#    #+#             */
/*   Updated: 2023/07/24 23:52:33 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_cmdpath(t_pipex *pipex)
{
	error_printer("Minishell: ", pipex->command[0], NO_CMD);
	free_pipex_all(pipex);
	exit(127);
}

void	error_permission(t_pipex *pipex)
{
	error_printer("Minishell: ", pipex->command[0], NO_PERM);
	free_pipex_all(pipex);
	exit(126);
}

void	is_directory(t_pipex *pipex)
{
	DIR	*dir;

	dir = opendir(pipex->command[0]);
	if (dir)
	{
		closedir(dir);
		error_printer("Minishell: ", pipex->command[0], DIR_ERR);
		free_pipex_all(pipex);
		exit(126);
	}
}
