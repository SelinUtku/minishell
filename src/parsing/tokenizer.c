/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:23:52 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/18 12:25:30 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_token_node(t_shell *shell, t_type type, char *str)
{
	t_token	*new;
	t_token	*last;

	new = my_malloc(&shell->garbage, 1, sizeof(t_token));
	new->type = type;
	new->str = str;
	if (shell->token == NULL)
	{
		new->next = NULL;
		shell->token = new;
	}
	else
	{
		last = shell->token;
		while (last->next != NULL)
			last = last->next;
		new->next = NULL;
		last->next = new;
	}
}

void	add_token_next(t_shell *shell, t_token *token, t_type type, char *str)
{
	t_token	*new;
	t_token	*temp;

	new = my_malloc(&shell->garbage, 1, sizeof(t_token));
	new->type = type;
	new->str = str;
	temp = token->next;
	token->next = new;
	new->next = temp;
}

void	examine_type(t_shell *shell)
{
	while (shell->input[shell->i] != '\0')
	{
		if (is_input_redirection(shell))
			;
		else if (is_output_redirection(shell))
			;
		else if (is_heredoc(shell))
			;
		else if (is_output_redirection_append(shell))
			;
		else if (is_pipe(shell))
			;
		else if (is_word(shell))
			;
		ft_isspace(shell);
	}
}

bool	is_pipe(t_shell *shell)
{
	if (shell->input[shell->i] == '|')
	{
		add_token_node(shell, PIPE, shell_strdup(shell, "|"));
		shell->i++;
		return (true);
	}
	return (false);
}

void	ft_isspace(t_shell *shell)
{
	while (shell->input[shell->i] == 32  && shell->input[shell->i] != '\0')
		shell->i++;
}

bool	is_word(t_shell *shell)
{
	int		start;
	char	*str;

	if (ft_strchr(WORD_DELIMITERS, shell->input[shell->i]) == 0)
	{
		start = shell->i;
		while (ft_strchr(WORD_DELIMITERS, shell->input[shell->i]) == 0)
		{
			if (shell->input[shell->i] == '\'')
				s_quote_state(shell);
			else if (shell->input[shell->i] == '\"')
				d_quote_state(shell);
			else
				shell->i++;
		}
		str = shell_substr(shell, shell->input, start, shell->i - start);
		add_token_node(shell, WORD, str);
		return (true);
	}
	return (false);
}

void	s_quote_state(t_shell *shell)
{
	shell->i++;
	while (shell->input[shell->i] != '\'' && shell->input[shell->i] != '\0')
		shell->i++;
	if (shell->input[shell->i] == '\'')
		shell->i++;
}

void	d_quote_state(t_shell *shell)
{
	shell->i++;
	while (shell->input[shell->i] != '\"' && shell->input[shell->i] != '\0')
		shell->i++;
	if (shell->input[shell->i] == '\"')
		shell->i++;
}
