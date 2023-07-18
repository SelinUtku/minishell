/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 03:27:52 by sutku             #+#    #+#             */
/*   Updated: 2023/07/18 08:37:31 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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

char	*merge_expanded_words(t_shell *shell)
{
	char	*temp;

	if (shell->exp_front)
	{
		temp = shell_strdup(shell, shell->exp_front->content);
		dequeue(&shell->exp_front);
	}
	while (shell->exp_front)
	{
		temp = shell_strjoin(shell, temp, shell->exp_front->content);
		dequeue(&shell->exp_front);
	}
	return (temp);
}

void	heredoc_expand(t_shell *shell, char *str, t_type type)
{
	int	start;
	int	*i;
	int	j;

	j = 0;
	i = &j;
	start = 0;
	while (str[*i] != '\0')
	{
		if (str[*i] == '$')
		{
			if (*i != start)
				enqueue(&shell->exp_front, &shell->exp_rear, \
				shell_substr(shell, str, start, *i - start));
			dollar_func(shell, str, i);
			start = (*i);
			(*i)--;
		}
		(*i)++;
	}
	if (*i != start)
		enqueue(&shell->exp_front, &shell->exp_rear, \
		shell_substr(shell, str, start, *i - start));
}

void	change_token_values(t_shell *shell, t_token *here, t_token *temp_token, char *file_name)
{
	here->type = 1;
	del_one_from_garbage(&shell->garbage, here->str);
	here->str = shell_strdup(shell, "<");
	temp_token->type = 5;
	temp_token->str = shell_strdup(shell, file_name);
	del_one_from_garbage(&shell->garbage, file_name);
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
	if (temp_token->type == 9)
	{
		ft_putstr_fd(str, fd);
		free(str);
	}
	else
	{
		heredoc_expand(shell, str, temp_token->type);
		free(str);
		ft_putstr_fd(merge_expanded_words(shell), fd);
	}
	return (1);
}

void	here_doc(t_shell *shell)
{
	char	*file_name;
	int		fd;
	t_token	*temp_token;

	shell->num_heredoc = 0;
	if (!shell->front || !shell->front->content)
		return ;
	temp_token = shell->front->content;
	while (temp_token)
	{
		if (temp_token->type == 0)
		{
			file_name = heredoc_file_name(shell, shell->num_heredoc);
			fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);// open _file ile cagir fd kontrolu orada olacak
			shell->num_heredoc++;
			while (1)
			{
				if (execute_heredoc(shell, temp_token->next, fd) == 0)// eger syntax error varsa yani delimiter yoksa segfault cunku nexte gitmeye calisiyorum
					break ;
			}
			close(fd);
			change_token_values(shell, temp_token, temp_token->next, file_name);
			temp_token = temp_token->next;
		}
		temp_token = temp_token->next;
	}
}

void	unlink_heredocs(t_shell *shell)
{
	int	i;
	t_token	*temp;

	i = 0;
	if (shell->num_heredoc)
		temp = shell->front->content;
	while (i < shell->num_heredoc && temp)
	{
		if (temp->type == 5)
		{
			unlink(temp->str);
			i++;
		}
		temp = temp->next;
	}
}