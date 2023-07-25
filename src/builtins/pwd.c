/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 03:09:49 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/25 20:59:49 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(char **str)
{
	char	*ptr;

	ptr = getcwd(NULL, 0);
	if (str[1] && str[1][0] == '-' && str[1][1])
	{
		error_invalid_option(str);
		return ;
	}
	if (!ptr)
	{
		perror("pwd");
		g_exit_status = 1;
		return ;
	}
	ft_putendl_fd(ptr, STDOUT_FILENO);
	free(ptr);
	g_exit_status = 0;
	return ;
}
