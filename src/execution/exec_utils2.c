/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:04:09 by sutku             #+#    #+#             */
/*   Updated: 2023/07/25 21:04:19 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	my_waitpid(t_pipex *pipex)
{
	int	i;
	int	status;

	i = -1;
	while (++i < pipex->num_commands)
		waitpid(pipex->pid[i], &status, 0);
	free_pipex_all(pipex);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}

char	**command_pointer(t_token *child)
{
	t_token	*temp;
	char	**str;
	int		i;

	temp = child;
	i = 0;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == WORD)
			i++;
		temp = temp->next;
	}
	temp = child;
	str = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == WORD)
		{
			str[i] = temp->str;
			i++;
		}
		temp = temp->next;
	}
	return (str[i] = NULL, str);
}
