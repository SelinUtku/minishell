/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 04:10:58 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/19 02:21:18 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	input_dup2(int input)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		perror("dup2");
		// free_pipex(pipex);
		exit(1);
	}
	if (input)
		close(input);
}

void	output_dup2(int output)
{
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		// free_pipex(pipex);
		exit(1);
	}
	if (output != 1)
		close(output);
}

void	my_waitpid(t_shell *shell, t_pipex *pipex)
{
	int	i;
	int	status;

	i = -1;
	while (++i < pipex->num_commands)
		waitpid(pipex->pid[i], &status, 0);
	free(pipex->pid);
	free_int_dubleptr(pipex->pipeline, pipex->num_commands - 1);
	if (WIFEXITED(status))
		shell->status = WEXITSTATUS(status);
}

int	open_file(char *filename, int flag)
{
	int	fd;

	if (flag == INPUT_R)
	{
		fd = open(filename, O_RDONLY);
		if (fd < 0)
		{
			// free_pipex(pipex);
			perror("pipex: input");
			exit(EXIT_FAILURE);
		}
		return (fd);
	}
	else if (flag == OUTPUT_R_APPEND)
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (flag == OUTPUT_R)
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0 || (access(filename, W_OK) != 0))
	{
		// free_pipex(pipex);
		perror("pipex: output");
		// exit(EXIT_FAILURE);
	}
	return (fd);
}