/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 04:02:51 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/25 20:54:07 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(char **str)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (check_echo_flag(str[i]))
	{
		new_line = 0;
		++i;
	}
	while (str[i])
	{
		ft_putstr_fd(str[i], STDOUT_FILENO);
		++i;
		if (str[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_exit_status = 0;
}

int	check_echo_flag(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '-' && str[i + 1] != '\0')
	{
		while (str[++i] != '\0')
		{
			if (str[i] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}
