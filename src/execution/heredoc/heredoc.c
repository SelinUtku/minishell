/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 03:27:52 by sutku             #+#    #+#             */
/*   Updated: 2023/07/24 14:43:48 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	here_doc(t_shell *shell)
{
	int		fd;
	char	*file_name;
	t_token	*token;
	t_queue	*que;

	shell->num_heredoc = 0;
	if (!shell->front || !shell->front->content)
		return ;
	que = shell->front;
	while (que)
	{
		token = (t_token *)que->content;
		if (token->type == HEREDOC)
		{
			file_name = heredoc_file_name(shell, shell->num_heredoc);
			fd = open_file(NULL, file_name, OUTPUT_R, 0);
			shell->num_heredoc++;
			while (1)
				if (execute_heredoc(shell, token->next, fd) == 0)
					break ;
			close(fd);
			change_token_values(shell, token, file_name);
		}
		que = que->next;
	}
}

void	heredoc_expand(t_shell *shell, char *str, t_type type)
{
	int	start;
	int	i;

	i = 0;
	start = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (i != start)
				enqueue(shell, &shell->exp_front, &shell->exp_rear, \
				shell_substr(shell, str, start, i - start));
			if_dollar_sign(shell, str, &i);
			start = i;
			i--;
		}
		i++;
	}
	if (i != start)
		enqueue(shell, &shell->exp_front, &shell->exp_rear, \
		shell_substr(shell, str, start, i - start));
}

void	change_token_values(t_shell *shell, t_token *token, char *file)
{
	token->type = INPUT_R;
	del_one_from_garbage(&shell->garbage, token->str);
	token->str = shell_strdup(shell, "<");
	token->next->type = FILENAME;
	del_one_from_garbage(&shell->garbage, token->next->str);
	token->next->str = shell_strdup(shell, file);
	del_one_from_garbage(&shell->garbage, file);
}

int	execute_heredoc(t_shell *shell, t_token *temp_token, int fd)
{
	char	*str;
	int		len;

	str = NULL;
	write(0, "> ", 2);
	str = get_next_line(STDIN_FILENO);
	if (delimiter_str_cmp(temp_token->str, str) == 0)
		return (free(str), 0);
	if (temp_token->type == Q_DELIMITER)
	{
		ft_putstr_fd(str, fd);
		free(str);
	}
	else
	{
		heredoc_expand(shell, str, temp_token->type);
		free(str);
		ft_putstr_fd(merge_queue(shell, temp_token), fd);
	}
	return (1);
}
