/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 03:55:30 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/07 22:09:37 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	delete_env_var(t_shell *shell, char *var)
{
	int		i;
	int		j;
	int		index_var;
	char	**temp;

	temp = shell->my_env;
	i = ft_double_strlen(temp);
	index_var = ft_getenv(temp, var);
	if (index_var != -1)
	{
		shell->my_env = my_malloc(&shell->garbage, i, sizeof(char *));
		i = 0;
		j = 0;
		while (temp && temp[i])
		{
			if (i != index_var)
				shell->my_env[j] = shell_strdup(shell, temp[i]);
			else
				j--;
			i++;
			j++;
		}
		shell->my_env[j] = NULL;
		// free(temp); double del one free
	}
}
