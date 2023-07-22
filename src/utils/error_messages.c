/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 04:51:11 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/22 04:52:15 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_not_valid_identifier(t_shell *shell, char *str1, char *str2)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(str2, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	shell->status = 1;
}

void	error_invalid_option(t_shell *shell, char **str)
{
	ft_putstr_fd(str[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putchar_fd(str[1][0], 2);
	if (str[1][1])
		ft_putchar_fd(str[1][1], 2);
	ft_putendl_fd(": invalid option", 2);
	shell->status = 2;
}

void	error_printer(char *str1, char *str2, char *str3)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putendl_fd(str3, 2);
}
