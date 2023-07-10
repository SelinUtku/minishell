/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 02:25:13 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/09 20:43:59 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pipe_counter(t_shell *shell)
{
	t_token *temp;
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

void	pipex(t_shell *shell, char **envp)
{
	t_pipex	*pipex;
	int		number_of_pipes;

	number_of_pipes = pipe_counter(shell);
	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	pipex->num_commands = number_of_pipes + 1;
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
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (++i < num)
	{
		pipex->pipeline[i] = (int *)malloc(sizeof(int) * 2);
		if (pipex->pipeline[i] == NULL)
		{
			free_int_dubleptr(pipex->pipeline, i);
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		if (pipe(pipex->pipeline[i]) == -1)
		{
			free_int_dubleptr(pipex->pipeline, num);
			perror("pipe");
			exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
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
			exit(EXIT_FAILURE);
		}
		exec_child_process(shell, pipex, i);
	}
}

t_token	*find_right_token(t_shell *shell, int num_pipe)
{
	t_token	*temp;
	int		i;

	temp = shell->token;
	i = 0;
	while (temp && i < num_pipe)
	{
		if (temp->type == 6)
			i++;
		temp = temp->next;
	}
	return (temp);
}

void	handle_redirections(t_shell *shell, t_token *blaa, t_pipex *pipex)
{
	int	fd;
	t_token *child;

	child = blaa;
	while (child && child->type != 6)
	{
		if (child->type == INPUT_R)
		{
			fd = open_file(child->next->str, INPUT_R, pipex);
			input_dup2(fd);
			close(fd);
		}
		else if (child->type == OUTPUT_R)
		{
			fd = open_file(child->next->str, OUTPUT_R, pipex);
			output_dup2(fd);
			close(fd);
		}
		else if (child->type == OUTPUT_R_APPEND)
		{
			fd = open_file(child->next->str, OUTPUT_R, pipex);
			output_dup2(fd);
			close(fd);
		}
		child = child->next;
	}
}

void	exec_child_process(t_shell *shell,t_pipex *pipex, int i)
{
	int		fd;
	t_token	*child;

	if (pipex->pid[i] == 0)
	{
		child = find_right_token(shell, i);
		if (pipex->num_commands != 1)
		{
			if (i == 0)
				output_dup2(pipex->pipeline[i][1]);
			else if (i == pipex->num_commands - 1)
				input_dup2(pipex->pipeline[i - 1][0]);
			else
			{
				input_dup2(pipex->pipeline[i - 1][0]);
				output_dup2(pipex->pipeline[i][1]);
			}
		}
		handle_redirections(shell, child, pipex);
		command_pointer(child, pipex);
		close_pipes(pipex);
		execve(get_command_path(pipex), pipex->command, pipex->envp);
		clean_garbage(&shell->garbage);
		// free(pipex->cmd_path);
		exit(EXIT_FAILURE);
	}
}

void	command_pointer(t_token *child, t_pipex *pipex)
{
	t_token	*temp;
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
	pipex->command = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (temp && temp->type != 6)
	{
		if (temp->type == WORD)
		{
			pipex->command[i] = ft_strdup(temp->str);
			i++;
		}
		temp = temp->next;
	}
	pipex->command[i] = NULL;
}

void	free_pipex(t_pipex *pipex)
{
	free(pipex->pid);
	free_int_dubleptr(pipex->pipeline, pipex->num_commands - 1);
	free_char_dubleptr(pipex->command);
}
