/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 03:37:42 by Cutku             #+#    #+#             */
/*   Updated: 2023/06/26 03:56:50 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_env_var(t_shell *shell, char *var, char *value)
{
	int		index;
	char	*temp;

	index = ft_getenv(shell->my_env, var);
	if (index != -1)
	{
		temp = shell->my_env[index];
		shell->my_env[index] = ft_strjoin(var, value);
		free(temp);
		// free(var);
		// free(value);Parsingden kaynakli linked listte olabilirler orada da free atilabilir.
	}
}

void	append_env_var(t_shell *shell, char *var, char *value)//export +=
{
	int		index;
	char	*temp;

	index = ft_getenv(shell->my_env, var);
	if (index != -1)
	{
		temp = shell->my_env[index];
		shell->my_env[index] = ft_strjoin(shell->my_env[index], value);
		free(temp);
		// free(var);
		// free(value);Parsingden kaynakli linked listte olabilirler orada da free atilabilir.
	}
}

void	create_env_var(t_shell *shell, char *var, char *value)//export
{
	char	**temp;
	int		i;

	temp = shell->my_env;
	shell->my_env = malloc((ft_double_strlen(temp) + 2) * sizeof(char *));
	i = 0;
	while (temp && temp[i])
	{
		shell->my_env[i] = temp[i];
		i++;
	}
	shell->my_env[i] = ft_strjoin(var, value);
	shell->my_env[i + 1] = NULL;
	free(temp);
}
