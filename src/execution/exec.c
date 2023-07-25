/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 02:25:13 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/25 21:04:24 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pipex(t_shell *shell)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	initialize_pipex(pipex);
	pipex->num_commands = shell->num_pipe + 1;
	pipex->envp = shell->my_env;
	create_pipelines(pipex, pipex->num_commands - 1);
	create_child_process(shell, pipex);
	close_pipes(pipex);
	my_waitpid(pipex);
}

void	create_pipelines(t_pipex *pipex, int num)
{
	int	i;

	i = -1;
	pipex->pipeline = (int **)malloc(num * sizeof(int *));
	if (pipex->pipeline == NULL)
	{
		g_exit_status = 1;
		return (perror("malloc"));
	}
	while (++i < num)
	{
		pipex->pipeline[i] = (int *)malloc(sizeof(int) * 2);
		if (pipex->pipeline[i] == NULL)
		{
			free_int_dubleptr(pipex->pipeline, i);
			g_exit_status = 1;
			return (perror("malloc"));
		}
		if (pipe(pipex->pipeline[i]) == -1)
		{
			free_int_dubleptr(pipex->pipeline, num);
			g_exit_status = 1;
			return (perror("pipe"));
		}
	}
}

void	create_child_process(t_shell *shell, t_pipex *pipex)
{
	int	i;

	pipex->pid = malloc(sizeof(pid_t) * (pipex->num_commands));
	if (pipex->pid == NULL)
	{
		free_int_dubleptr(pipex->pipeline, pipex->num_commands - 1);
		g_exit_status = 1;
		return (perror("malloc"));
	}
	i = -1;
	while (++i < pipex->num_commands)
	{
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
		{
			perror("Fork");
			free(pipex->pid);
			free_int_dubleptr(pipex->pipeline, pipex->num_commands - 1);
			g_exit_status = 1;
			return (perror("fork"));
		}
		exec_child_process(shell, pipex, i);
	}
}

void	exec_child_process(t_shell *shell, t_pipex *pipex, int i)
{
	char	*cmd_path;
	t_token	*child;

	if (pipex->pid[i] == 0)
	{
		signals_child();
		child = find_right_token(shell, i);
		pipe_redirections(pipex, i);
		handle_redirections(pipex, child, 1);
		pipex->command = command_pointer(child);
		if (!pipex->command || !pipex->command[0])
		{
			free_pipex_all(pipex);
			exit(0);
		}
		if (is_builtin(pipex->command[0]))
			exec_builtin(shell, pipex->command, pipex);
		close_pipes(pipex);
		cmd_path = get_command_path(pipex);
		execve(cmd_path, pipex->command, pipex->envp);
		clean_garbage(&shell->garbage);
		free(cmd_path);
		free_pipex_all(pipex);
		exit(EXIT_FAILURE);
	}
}
