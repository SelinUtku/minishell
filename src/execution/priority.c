#include "../../include/minishell.h"

void	exec_order(t_shell *shell)
{
	t_token	*temp;

	temp = shell->token;
	if (temp && temp->type == PIPE)
	{
		temp->type = SYNTAX_ERROR;
		error_printer(SYNTAX_ERR_MSG, "|", "'");
		return ;
	}
	if (order_heredoc(shell, temp) == false)
		return ;
}

bool	order_heredoc(t_shell *shell, t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (is_syntax_error(shell, temp) == true)
			return (false);
		if (temp->type == 0)
		{
			enqueue(shell, &shell->front, &shell->rear, temp);
			temp = temp->next;
			temp->type = DELIMITER;
			if (ft_strchr(temp->str, '\'') || ft_strchr(temp->str, '\"'))
				temp->type = Q_DELIMITER;
			enqueue(shell, &shell->front, &shell->rear, temp);
		}
		temp = temp->next;
	}
	return (true);
}

bool	is_syntax_error(t_shell *shell, t_token *token)
{
	if (token->type == PIPE)
	{
		if (token->next == NULL || token->next->type == PIPE)
		{
			token->type = SYNTAX_ERROR;
			error_printer(SYNTAX_ERR_MSG, "|", "'");
			return (true);
		}
	}
	if (token->type >= 0 && token->type <= 3)
	{
		if (token->next == NULL || token->next->type != 7)
		{
			token->type = SYNTAX_ERROR;
			if (token->next != NULL)
				error_printer(SYNTAX_ERR_MSG, token->next->str, "'");
			else
				error_printer(SYNTAX_ERR_MSG, "newline", "'");
			return (true);
		}
		else
			token->next->type = FILENAME;
	}
	return (false);
}
