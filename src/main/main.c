

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
		get_input();
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

void	get_input(void)
{
	char	*input;
	char	*back_up;
	t_shell	*shell;

	// atexit(&leaks);
	shell = malloc(sizeof(t_shell));
	shell->i = 0;
	while (1)
	{
		shell->token = NULL;
		shell->garbage = NULL;
		shell->input = readline("MinisHELL$ ");
		if (shell->input == NULL || shell->input[0] == EOF \
		|| ft_strncmp(shell->input, "exit", 4) == 0)
		{
			free(shell->input);
			exit(EXIT_SUCCESS);
		}
		add_history(shell->input);
		examine_type(shell);
		print_token(shell->token);
		exec_order(shell);
		print_order(&shell->front);
		free(shell->input);
		clean_garbage(&shell->garbage);
		shell->i = 0;
	}
}
