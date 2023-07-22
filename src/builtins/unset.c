/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 03:55:30 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/22 07:42:27 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_unset(t_shell *shell, char **str)
{
	int	i;
	int	j;

	shell->status = 0;
	if (str[1] && str[1][0] == '-')
	{
		error_invalid_option(shell, str);
		return ;
	}
	i = 1;
	while (str[i])
	{
		if (is_valid_syntax_var(shell, str[i]) == ft_strlen(str[i]) \
		&& ft_strlen(str[i]) != 0)
			delete_env_var(shell, str[i]);
		else
			error_not_valid_identifier(shell, str[0], str[i]);
		i++;
	}
}

int	is_valid_syntax_var(t_shell *shell, char *str)
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
