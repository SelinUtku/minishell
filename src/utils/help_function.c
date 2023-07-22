/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 04:41:12 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/22 05:08:51 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_double_strlen(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*shell_strdup(t_shell *shell, const char *s1)
{
	int		len;
	char	*dst;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	dst = (char *)my_malloc(&shell->garbage, (len + 1), sizeof(char));
	while (i < len)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*shell_strjoin(t_shell *shell, char const *s1, char const *s2)
{
	unsigned int	len;
	char			*dst;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	dst = (char *)my_malloc(&shell->garbage, (len +1), sizeof(char));
	ft_memcpy(dst, s1, ft_strlen(s1));
	ft_memcpy(&dst[ft_strlen(s1)], s2, ft_strlen(s2));
	dst[len] = '\0';
	return (dst);
}

char	*shell_substr(t_shell *shell, char const *s, int start, int len)
{
	int		i;
	char	*ptr;
	int		size;

	if (!s)
		return (NULL);
	i = 0;
	if (start > ft_strlen(s))
		len = 0;
	size = ft_strlen(s) - start;
	if (len > size)
		len = size;
	ptr = (char *)my_malloc(&shell->garbage, (len + 1), sizeof(char));
	while (i < len && start < ft_strlen(s))
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_isspace(char	a)
{
	if (a == 32 || a == 9 || a == 10)
		return (1);
	return (0);
}
