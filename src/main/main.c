/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:50:44 by sutku             #+#    #+#             */
/*   Updated: 2023/06/09 03:10:43 by Cutku            ###   ########.fr       */
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
		get_input();
	}
	return (0);
}

void	get_input(void)
{
	char	*input;

	while (1)
	{
		input = readline("MinisHELL$ ");
		if (input == NULL || input[0] == EOF \
		|| ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		printf ("%s\n", input);
		free(input);
	}
}
