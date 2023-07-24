/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 03:14:28 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/23 17:41:45 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_no_arg(t_shell *shell)
{
	int	status;

	// ft_putendl_fd("exit", STDERR_FILENO);
	status = shell->status;
	free_shell(shell);
	exit(status);
}

void	exit_non_numeric(t_shell *shell, char **str)
{
	int	i;

	if (str[1][0] == '\0')
	{
		error_printer("Minishell: exit: ", str[1], EXIT_NON_NUM);
		free_shell(shell);
		exit(255);
	}
	i = 0;
	while (str[1][i] != '\0')
	{
		if (str[1][0] == '-' || str[1][0] == '+')
			i++;
		if (ft_isdigit(str[1][i]) == 0)
		{
			// ft_putendl_fd("exit", STDERR_FILENO);
			error_printer("Minishell: exit: ", str[1], EXIT_NON_NUM);
			free_shell(shell);
			exit(255);
		}
		i++;
	}
}

void	ft_exit(t_shell *shell, char **str)
{
	int	i;

	if (!str[1])
		exit_no_arg(shell);
	else
	{
		exit_non_numeric(shell, str);
		if (ft_double_strlen(str) > 2)
		{
			// ft_putendl_fd("exit", STDERR_FILENO);
			error_printer("Minishell: ", "exit: ", TOO_MNY_ARG);
			shell->status = 1;
		}
		else
		{
			// ft_putendl_fd("exit", STDERR_FILENO);
			exit(ft_atoi(str[1]) % 256);
		}
	}
}

void	free_shell(t_shell *shell)
{
	free(shell->input);
	clean_garbage(&shell->garbage);
	free(shell);
}
