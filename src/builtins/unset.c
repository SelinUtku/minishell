/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 03:55:30 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/25 20:59:12 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_unset(t_shell *shell, char **str)
{
	int	i;

	g_exit_status = 0;
	if (str[1] && str[1][0] == '-' && str[1][1])
	{
		error_invalid_option(str);
		return ;
	}
	i = 1;
	while (str[i])
	{
		if (is_valid_syntax_var(str[i]) == ft_strlen(str[i]) \
		&& ft_strlen(str[i]) != 0)
			delete_env_var(shell, str[i]);
		else
			error_not_valid_identifier(str[0], str[i]);
		i++;
	}
}

int	is_valid_syntax_var(char *str)
{
	int	i;
	int	valid;

	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (0);
	i = 1;
	valid = 1;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 1 || str[i] == '_')
			valid++;
		else
			return (valid);
		i++;
	}
	return (valid);
}
