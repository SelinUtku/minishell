/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 04:02:51 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/12 04:49:30 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_echo_flag(char *str);

void	ft_echo(t_shell *shell, char **str)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (check_echo_flag(str[i]))
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
}

int	check_echo_flag(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '-' && str[i + 1] != '\0')
	{
		while(str[++i] != '\0')
		{
			if (str[i] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}
