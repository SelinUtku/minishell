/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 03:14:28 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/14 15:25:21 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(t_shell *shell, char **str)
{
	int	status;
	int	i;

	if (!str[1])
	{
		// ft_putendl_fd("exit", 0);
		status = shell->status;
		free(shell->input);
		clean_garbage(&shell->garbage);
		free(shell);
		exit(status);
	}
	else
	{
		i = 0;
		while (str[1][i] != '\0')
		{
			if (str[1][0] ==  '-' || str[1][0] == '+' )
				i++;
			if (ft_isdigit(str[1][i]) == 0)
			{
				// ft_putendl_fd("exit", 1);
				ft_putstr_fd("Minishell: exit: ", 2);
				ft_putstr_fd(str[1], 2);
				ft_putendl_fd(": numeric argument required", 2);
				free(shell->input);
				clean_garbage(&shell->garbage);
				free(shell);
				exit(255);
			}
			i++;
		}
		if (ft_double_strlen(str) > 2)
		{
				// ft_putendl_fd("exit", 1);
				ft_putstr_fd("Minishell: exit: ", 2);
				ft_putendl_fd("too many arguments", 2);
				shell->status = 1;
		}
		else
		{
			if (str[1][0] == '\0')
			{
				ft_putstr_fd("Minishell: exit: ", 2);
				ft_putstr_fd(str[1], 2);
				ft_putendl_fd(": numeric argument required", 2);
				free(shell->input);
				clean_garbage(&shell->garbage);
				free(shell);
				exit(255);
			}
			// ft_putendl_fd("exit", 1);
			exit(ft_atoi(str[1]) % 256);
		}
	}
}
