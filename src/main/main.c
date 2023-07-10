/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 04:02:59 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/10 02:47:27 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	if (argc != 1)
	{
		write (2, "Minishell does not take any arguments\n", 39);
		return (1);
	}
	else
	{
		get_input(env);
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
		printf("Token String : %s\n", temp->str);
		temp = temp->next;
	}
}

void	print_order(t_queue **front)
{
	t_queue	*temp;

	temp = *front;
	printf("EXEC ORDER\n");
	while (*front && (*front)->content)
	{
		printf("Token Type : %d ", ((t_token *)(*front)->content)->type);
		printf("Token String : %s\n", ((t_token *)(*front)->content)->str);
		dequeue(front);
		// temp = temp->next;
	}
}
void	leaks(void)
{
	system("leaks minishell");
}

void	init_shell_struct(t_shell *shell)
{
	shell->i = 0;
	shell->token = NULL;
	shell->front = NULL;
	shell->rear = NULL;
	shell->exp_front = NULL;
	shell->exp_rear = NULL;
}

void	get_input(char **env)
{
	char	*input;
	char	*back_up;
	t_shell	*shell;

	// atexit(&leaks);
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return ;
	shell->garbage = NULL;
	init_shell_struct(shell);
	create_env(shell, env);
	while (1)
	{
		init_shell_struct(shell);
		shell->input = readline("MinisHELL$ ");
		ft_exit(shell);
		add_history(shell->input);
		examine_type(shell);
		// print_token(shell->token);
		exec_order(shell);
		is_expandable(shell);
		print_order(&shell->front);
		// pipex(shell, shell->my_env);
		print_token(shell->token);
		free(shell->input);
	}
}

