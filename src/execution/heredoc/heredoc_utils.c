/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:48:30 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/24 03:55:12 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	heredoc_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

int	delimiter_str_cmp(char *del, char *str)
{
	int	i;
	int	len;

	i = 0;
	if (!del || !str)
		return (0);
	len = heredoc_strlen(str);
	if (len != ft_strlen(del))
		return (1);
	while (i < len)
	{
		if (str[i] != del[i])
			return (1);
		i++;
	}
	return (0);
}

char	*heredoc_file_name(t_shell *shell, int counter)
{
	char	*file_name;
	char	*c;

	c = ft_itoa(counter);
	file_name = shell_strjoin(shell, "heredoc_tmp_", c);
	free (c);
	return (file_name);
}

void	unlink_heredocs(t_shell *shell)
{
	int		i;
	t_queue	*temp;

	i = 0;
	if (shell->num_heredoc)
		temp = shell->front;
	while (i < shell->num_heredoc && temp)
	{
		if (((t_token *)temp->content)->type == FILENAME)
		{
			unlink(((t_token *)temp->content)->str);
			i++;
		}
		temp = temp->next;
	}
}
