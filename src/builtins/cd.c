/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 02:04:07 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/24 01:28:36 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_oldpwd(t_shell *shell, char *current_pwd)
{
	static int		check = 0;
	int				i;

	if (check == 0)
	{
		check++;
		add_env_var(shell, shell_strdup(shell, "OLDPWD="), current_pwd);
	}
	else
		update_env_var(shell, shell_strdup(shell, "OLDPWD="), current_pwd);
	free(current_pwd);
}

void	cd_to_home(t_shell *shell, char *current_pwd)
{
	char	*str;
	int		index;

	index = ft_getenv(shell->my_env, "HOME");
	if (index == -1)
	{
		shell->status = 1;
		error_printer("Minishell: ", "cd: ", "HOME not set");
		return ;
	}
	str = value_of_expandable(shell, "HOME");
	if (chdir(str) == -1)
		return (shell->status = 1, perror("cd:"));
	update_env_var(shell, shell_strdup(shell, "PWD="), str);
	update_oldpwd(shell, current_pwd);
	shell->status = 0;
}

void	ft_cd(t_shell *shell, char *path)
{
	char	*str;
	int		index;
	char	*current_pwd;

	shell->status = 0;
	current_pwd = getcwd(NULL, 0);
	if (!path)
		cd_to_home(shell, current_pwd);
	else if (!*path)
		return ;
	else
	{
		if (chdir(path) == -1)
		{
			error_printer("Minishell: cd: ", path, NO_FILE);
			shell->status = 1;
			return (free(current_pwd));
		}
		str = getcwd(NULL, 0);
		update_env_var(shell, shell_strdup(shell, "PWD="), str);
		free(str);
		update_oldpwd(shell, current_pwd);
	}
}
