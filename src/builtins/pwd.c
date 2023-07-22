/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 03:09:49 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/22 22:03:21 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(t_shell *shell, char **str)
{
	char	*ptr;

	ptr = getcwd(NULL, 0);
	if (str[1] && str[1][0] == '-' && str[1][1])
	{
		error_invalid_option(shell, str);
		return ;
	}
	if (!ptr)
	{
		perror("pwd");
		shell->status = 1;
		return ;
	}
	ft_putendl_fd(ptr, STDOUT_FILENO);
	free(ptr);
	shell->status = 0;
	return ;
}
