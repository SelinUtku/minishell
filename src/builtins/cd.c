/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 02:04:07 by Cutku             #+#    #+#             */
/*   Updated: 2023/06/26 04:01:38 by Cutku            ###   ########.fr       */
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
		return ;
	}
	if (check == 0)
	{
		check++;
		create_env_var(shell, "OLDPWD=", temp);
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
			return ;// path bulunamadi
		if (chdir(str) == -1)
		{
			perror("chdir");// error mesajlari icin ayri fonksiyon lazim
			return ;
		}
		update_env_var(shell, "PWD=", str);
	}
	else
	{
		if (chdir(path) == -1)
		{
			perror("chdir");// error mesajlari icin ayri fonksiyon lazim
			return ;
		}
		str = getcwd(NULL, 0);// bu malloclanmis veri donerken getenv sadece string donuyor malloclanmamis
		update_env_var(shell, "PWD=", str);
		free(str);
	}
}


/*
Oldpwd varsa sil. Ilk aldigimiz env de olmadigindan emin ol.***
Updater fonksiyonu yaz. Var olan bir env variable icin. PWD, OLDPWD var mesela yeni deger atamak istiyorum guncelle.
Setter fonksiyonu yaz. Variable env de hic yok ise girecegi.
Eger veri sadece = degil, += ise sonuna ekleme yapacagimiz icin ona uygun bir fonksiyon yaz. += dir mi sadece = dir mi onu parseda kontrol ederiz.


*/