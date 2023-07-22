/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 05:05:14 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/22 21:02:29 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_env_path(char **envp)
{
	char	**my_envp;
	int		i;

	i = 0;
	my_envp = envp;
	if (my_envp && my_envp[i])
	{
		while (my_envp[i])
		{
			if (ft_strncmp(my_envp[i], "PATH=", 5) == 0)
				return (ft_split(my_envp[i] + 5, ':'));
			i++;
		}
	}
	return (ft_split(getcwd(NULL, 0), ':'));
}

char	*get_command_path(t_pipex *pipex)
{
	int		i;
	char	*ptr;

	if (is_exact_path(pipex) != NULL)
		return (is_exact_path(pipex));
	i = -1;
	pipex->all_paths = get_env_path(pipex->envp);
	while (pipex->all_paths[++i] != NULL)
	{
		ptr = pipex->all_paths[i];
		pipex->all_paths[i] = ft_strjoin(pipex->all_paths[i], "/");
		free(ptr);
		pipex->cmd_path = ft_strjoin(pipex->all_paths[i], pipex->command[0]);
		if (access(pipex->cmd_path, F_OK) == 0)
		{
			if (access(pipex->cmd_path, X_OK) == 0)
				return (free_char_dubleptr(pipex->all_paths), pipex->cmd_path);
			else
			{
				free_char_dubleptr(pipex->all_paths);
				error_permission(pipex);
			}
		}
	}
	return (error_cmdpath(pipex), NULL);
}

char	*is_exact_path(t_pipex *pipex)
{
	if (!pipex->command[0][0])
		error_cmdpath(pipex);
	else if (ft_strchr(pipex->command[0], '/') || pipex->command[0][0] == '.')
	{
		if (ft_strchr(pipex->command[0], '/') == 0 && pipex->command[0][0] == '.')
			error_cmdpath(pipex);
		is_directory(pipex);
		if (access(pipex->command[0], F_OK) == 0)
		{
			if (access(pipex->command[0], X_OK) == 0)
				return (pipex->command[0]);
			else
				error_permission(pipex);
		}
		else
			error_cmdpath(pipex);
	}
	return (NULL);
}

void	error_cmdpath(t_pipex *pipex)
{

	error_printer("Minishell: ", pipex->command[0], NO_CMD);
	// free_char_dubleptr(pipex->all_paths);
	// free_pipex(pipex);
	exit(127);
}
void	error_permission(t_pipex *pipex)
{
	error_printer("Minishell: ", pipex->command[0], NO_PERM);
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
		exit(126);
	}
}