

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

void	print_token(t_token **token)
{
	t_token	*temp;

	temp = *token;
	while (temp)
	{
		printf("Token Type : %d ", temp->type);
		printf("Token String : %s$\n", temp->str);
		temp = temp->next;
	}
}

void	get_input(void)
{
	char	*input;
	char	*back_up;
	t_token	*token;

	token = NULL;
	while (1)
	{
		input = readline("MinisHELL$ ");
		back_up = input;
		if (input == NULL || input[0] == EOF \
		|| ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		// examine_type(&token, &input);
		split_pipes(&token, &input);
		print_token(&token);
		free(back_up);
	}
}
