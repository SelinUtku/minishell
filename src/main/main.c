/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 04:02:59 by Cutku             #+#    #+#             */
/*   Updated: 2023/06/29 05:28:44 by Cutku            ###   ########.fr       */
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
	while (temp && temp->token)
	{
		printf("Token Type : %d ", temp->token->type);
		printf("Token String : %s$\n", temp->token->str);
		temp = temp->next;
	}
}
void	leaks(void)
{
	system("leaks minishell");
}

void	get_input(char **env)
{
	char	*input;
	char	*back_up;
	t_shell	*shell;

	// atexit(&leaks);
	shell = malloc(sizeof(t_shell));
	shell->i = 0;
	create_env(shell, env);
	while (1)
	{
		shell->token = NULL;
		shell->garbage = NULL;
		shell->input = readline("MinisHELL$ ");
		// ft_cd(shell, shell->input);
		// ft_env(shell);
		// printf("\n\n\n");
		// delete_env_var(shell, "data");
		// ft_env(shell);
		// if (ft_strncmp(shell->input, "cd", 2) == 0)
		// 	printf("%s\n", value_of_expandable(shell, shell->input + 3));
		ft_exit(shell);
		add_history(shell->input);
		examine_type(shell);
		print_token(shell->token);
		is_expandable(shell);
		exec_order(shell);
		print_order(&shell->front);
		free(shell->input);
		clean_garbage(&shell->garbage);
		shell->i = 0;
	}
}
