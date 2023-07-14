/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 03:55:30 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/14 16:22:39 by Cutku            ###   ########.fr       */
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
		if (is_valid_syntax_var(shell, str[i]) == 1)
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

	valid = 0;
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 1 || str[i] == '_')
			valid = 1;
		else
			return (0);
		i++;
	}
	return (valid);
}

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
