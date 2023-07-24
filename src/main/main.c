/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 04:02:59 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/24 16:49:40 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_syntax_error(t_shell *shell)
{
	t_token	*temp;

	temp = shell->token;
	while (temp)
	{
		if (temp->type == SYNTAX_ERROR)
			return (shell->status = 258, 1);
		temp = temp->next;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 1 && argv)
	{
		write (2, "Minishell does not take any arguments\n", 39);
		return (1);
	}
	else
	{
		return (get_input(env));
	}
	return (0);
}

void	print_token(t_token *token)
{
	t_token	*temp;

	temp = token;
	printf("INPUT ORDER\n");
	while (temp)
	{
		printf("Token Type : %d ", temp->type);
		printf("Token String : %s$\n", temp->str);
		temp = temp->next;
	}
}

void	print_order(t_queue **front)
{
	t_queue	*temp;

	temp = *front;
	printf("EXEC ORDER\n");
	while (temp && temp->content)
	{
		printf("Token Type : %d ", ((t_token *)temp->content)->type);
		printf("Token String : %s\n", ((t_token *)temp->content)->str);
		// dequeue(front);
		temp = temp->next;
	}
}
void	leaks(void)
{
	system("leaks minishell");
}

void	init_shell_struct(t_shell *shell)
{
	shell->token = NULL;
	shell->front = NULL;
	shell->rear = NULL;
	shell->exp_front = NULL;
	shell->exp_rear = NULL;
}

int	get_input(char **env)
{
	t_shell	*shell;

	// atexit(&leaks);
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (0);
	shell->status = 0;
	shell->garbage = NULL;
	shell->export_list = NULL;
	init_shell_struct(shell);
	create_env(shell, env);
	create_export_list(shell);
	while (1)
	{
		// signals(shell);
		// if (isatty(fileno(stdin)))
		// 	shell->input = readline("MinisHell$ ");
		// else
		// {
			char *line;
			line = get_next_line(fileno(stdin));
			shell->input = ft_strtrim(line, "\n");
			free(line);
		// }
		// shell->input = readline("MinisHELL$ ");
		// ft_exit(shell);
		if (shell->input == NULL || shell->input[0] == EOF)
			exit(shell->status);
		add_history(shell->input);
		define_type(shell);
		// print_token(shell->token);
		exec_order(shell);
		is_expandable(shell);
		split_after_expand(shell);
		delete_quotes(shell);
		// print_order(&shell->front);
		here_doc(shell);
		if (check_syntax_error(shell) == 0)
		{
			shell->num_pipe = pipe_counter(shell);
			if (shell->num_pipe == 0)
			{
				char **str = command_pointer(shell->token);
				if (is_builtin(*str))
				{
					int fd_in = dup(STDIN_FILENO);
					int	fd_out = dup(STDOUT_FILENO);
					handle_redirections(shell, NULL, shell->token, 0);
					which_builtin(shell, str);
					input_dup2(fd_in, NULL, 0);
					output_dup2(fd_out, NULL, 0);
				}
				else
					pipex(shell, shell->my_env);
			}
			else
				pipex(shell, shell->my_env);
		}
		unlink_heredocs(shell);
		// print_token(shell->token);
		free(shell->input);
	}
	return (shell->status);

}


/*
heredoc open degistirdim
handle redirection input output dup2 pipex ve flag gonderdim

*/