/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 04:10:58 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/25 19:35:09 by sutku            ###   ########.fr       */
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
			return ;
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
			return ;
		if (pipex != NULL)
			free_pipex_all(pipex);
		exit(1);
	}
	close(output);
}

int	open_input_file(t_pipex *pipex, char *filename, int flag)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Minishell: input");
		if (flag == 0)
			return (-1);
		free_pipex_all(pipex);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	open_file(t_pipex *pipex, char *filename, int rdir, int flag)
{
	int	fd;

	fd = 0;
	if (rdir == INPUT_R)
	{
		fd = open_input_file(pipex, filename, flag);
		if (fd == -1)
			return (-1);
		return (fd);
	}
	else if (rdir == OUTPUT_R_APPEND)
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (rdir == OUTPUT_R)
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0 || (access(filename, W_OK) != 0))
	{
		perror("Minishell: output");
		if (flag == 0)
			return (1);
		if (pipex != NULL)
			free_pipex_all(pipex);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
