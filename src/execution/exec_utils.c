/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 23:17:43 by sutku             #+#    #+#             */
/*   Updated: 2023/07/24 23:21:34 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	initialize_pipex(t_pipex *pipex)
{
	pipex->pid = NULL;
	pipex->command = NULL;
	pipex->all_paths = NULL;
	pipex->pipeline = NULL;
	pipex->envp = NULL;
	pipex->cmd_path = NULL;
	pipex->num_commands = 0;
}

int	pipe_counter(t_shell *shell)
{
	t_token	*temp;
	int		i;

	temp = shell->token;
	i = 0;
	while (temp && temp->str)
	{
		if (temp->type == PIPE)
			i++;
		temp = temp->next;
	}
	return (i);
}

void	free_pipex_all_two(t_pipex *pipex)
{
	if (pipex->pid)
	{
		free(pipex->pid);
		pipex->pid = NULL;
	}
	if (pipex->pipeline)
	{
		free_int_dubleptr(pipex->pipeline, pipex->num_commands - 1);
		pipex->pipeline = NULL;
	}
	if (pipex)
	{
		free(pipex);
		pipex = NULL;
	}
}

void	free_pipex_all(t_pipex *pipex)
{
	if (pipex->cmd_path)
	{
		free(pipex->cmd_path);
		pipex->cmd_path = NULL;
	}
	if (pipex->all_paths)
	{
		free_char_dubleptr(pipex->all_paths);
		pipex->all_paths = NULL;
	}
	if (pipex->command)
	{
		free(pipex->command);
		pipex->command = NULL;
	}
	free_pipex_all_two(pipex);
}

t_token	*find_right_token(t_shell *shell, int num_pipe)
{
	t_token	*temp;
	int		i;

	temp = shell->token;
	i = 0;
	while (temp && i < num_pipe)
	{
		if (temp->type == PIPE)
			i++;
		temp = temp->next;
	}
	return (temp);
}
