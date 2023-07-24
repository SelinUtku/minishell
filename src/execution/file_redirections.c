/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 04:10:58 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/24 14:54:01 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	input_dup2(int input, t_pipex *pipex, int flag)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(input);
		if (flag == 0)
			return;
		// free_pipex(pipex);
		if (pipex != NULL)
			free_pipex_all(pipex);
		exit(1);
	}
	close(input);
}

void	output_dup2(int output, t_pipex *pipex, int flag)
{
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(output);
		if (flag == 0)
			return;
		if (pipex != NULL)
			free_pipex_all(pipex);
		exit(1);
	}
	close(output);
}

void	my_waitpid(t_shell *shell, t_pipex *pipex)
{
	int	i;
	int	status;

	i = -1;
	while (++i < pipex->num_commands)
		waitpid(pipex->pid[i], &status, 0);
	free_pipex_all(pipex);
	if (WIFEXITED(status))
		shell->status = WEXITSTATUS(status);
}

int	open_file(t_pipex *pipex, char *filename, int rdir, int flag)
{
	int	fd;

	if (rdir == INPUT_R)
	{
		fd = open(filename, O_RDONLY);
		if (fd < 0)
		{
			free_pipex_all(pipex);
			perror("Minishell: input");
			if (flag == 0)
				return (1);
			exit(EXIT_FAILURE);
		}
		return (fd);
	}
	else if (rdir == OUTPUT_R_APPEND)
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (rdir == OUTPUT_R)
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0 || (access(filename, W_OK) != 0))
	{
		if (pipex != NULL)
			free_pipex_all(pipex);
		perror("Minishell: output");
		if (flag == 0)
			return (1);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
