/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 03:09:49 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/14 04:44:18 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*ptr;

	ptr = getcwd(NULL, 0);
	if (!ptr)
	{
		perror("pwd");
		shell->status = 1;
		return ;
	}
	ft_putstr_fd(ptr, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(ptr);
	shell->status = 0;
	return ;
}
