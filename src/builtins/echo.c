/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 04:02:51 by Cutku             #+#    #+#             */
/*   Updated: 2023/06/26 09:24:30 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	ft_echo(t_shell *shell, t_token *var, int fd)
// {
// 	int	i;

// 	i = 0;
// 	if (var && var->str)
// 	{
// 		while (str[i])
// 	}
// 	ft_putstr_fd("\n", fd);
// }

int	check_echo_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] != '\0')
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


