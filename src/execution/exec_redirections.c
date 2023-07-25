/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 23:20:02 by sutku             #+#    #+#             */
/*   Updated: 2023/07/25 18:57:54 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	do_redirections(t_pipex *pipex, t_token *child, int flag)
{
	int	fd;

	if (child->type == INPUT_R)
	{
		fd = open_file(pipex, child->next->str, INPUT_R, flag);
		if (fd == -1)
			return (false);
		input_dup2(fd, pipex, flag);
	}
	else if (child->type == OUTPUT_R)
	{
		fd = open_file(pipex, child->next->str, OUTPUT_R, flag);
		if (fd == -1)
			return (false);
		output_dup2(fd, pipex, flag);
	}
	else if (child->type == OUTPUT_R_APPEND)
	{
		fd = open_file(pipex, child->next->str, OUTPUT_R_APPEND, flag);
		if (fd == -1)
			return (false);
		output_dup2(fd, pipex, flag);
	}
	return (true);
}

bool	handle_redirections(t_shell *shell, t_pipex *pipex, \
t_token *token, int flag)
{
	t_token	*child;

	child = token;
	while (child && child->type != 6)
	{
		if (check_ambiguous_redirect(shell, pipex, child, flag) == true)
			return (false);
		if (do_redirections(pipex, child, flag) == false)
			return (false);
		child = child->next;
	}
	return (true);
}

void	pipe_redirections(t_pipex *pipex, int i)
{
	if (pipex->num_commands != 1)
	{
		if (i == 0)
			output_dup2(pipex->pipeline[i][1], pipex, 1);
		else if (i == pipex->num_commands - 1)
			input_dup2(pipex->pipeline[i - 1][0], pipex, 1);
		else
		{
			input_dup2(pipex->pipeline[i - 1][0], pipex, 1);
			output_dup2(pipex->pipeline[i][1], pipex, 1);
		}
	}
}

bool	check_ambiguous_redirect(t_shell *shell, t_pipex *pipex, \
t_token *child, int flag)
{
	if (child->type <= 3 && child->type >= 0 && child->next->next \
	&& child->next->next->type == FILENAME)
	{
		error_printer("Minishell:", " ", "ambiguous redirect");
		if (flag == 0)
		{
			shell->status = 1;
			return (true);
		}
		if (pipex != NULL)
			free_pipex_all(pipex);
		exit(1);
	}
	return (false);
}
