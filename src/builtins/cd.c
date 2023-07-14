/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 02:04:07 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/14 05:24:18 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_oldpwd(t_shell *shell)
{
	static int		check = 0;
	char			*temp;
	int				i;

	temp = getcwd(NULL, 0);
	if (!temp)
	{
		perror("getcwd");
		shell->status = 1;
		return ;
	}
	if (check == 0)
	{
		check++;
		add_env_var(shell, "OLDPWD=", temp);
	}
	else
		update_env_var(shell, "OLDPWD=", temp);
	free(temp);
}

void	ft_cd(t_shell *shell, char *path)
{
	char	*str;

	update_oldpwd(shell);
	if (!path || !*path)// belki sadece yildizli tutmamiz gerekir	
	{
		str = getenv("HOME=");
		if (!str)
			return ;
		if (chdir(str) == -1)
			return (shell->status = 1, perror("cd:"));
		update_env_var(shell, "PWD=", str);
	}
	else
	{
		if (chdir(path) == -1)
			return (shell->status = 1, ft_putstr_fd("MinisHell: cd: ", 2), perror(path));
		str = getcwd(NULL, 0);
		update_env_var(shell, "PWD=", str);
		free(str);
	}
	shell->status = 0;
}
