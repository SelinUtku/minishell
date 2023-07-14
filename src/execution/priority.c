#include "../../include/minishell.h"

void	exec_order(t_shell *shell)
{
	t_token	*temp;

	temp = shell->token;
	if (temp && temp->type == PIPE)
	{
		temp->type = SYNTAX_ERROR;
		ft_putendl_fd("Minishell: syntax error near unexpected token `|'", 2);
		return ;
	}
	if (order_heredoc(shell, temp) == false)
		return ;
	while (temp)
	{
		order_redirections(shell, temp);
		while (temp && temp->type != 6)
		{
			if (temp->type == 7)
				enqueue(&shell->front, &shell->rear, temp);
			temp = temp->next;
		}
		if (temp)
		{
			enqueue(&shell->front, &shell->rear, temp);
			temp = temp->next;
		}
	}
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
			enqueue(&shell->front, &shell->rear, temp);
			// enqueue(&shell->front, &shell->rear, shell_strdup(temp->str), temp->type);
			temp = temp->next;
			temp->type = 4;
			enqueue(&shell->front, &shell->rear, temp);
		}
		temp = temp->next;
	}
	return (true);
}

void	order_redirections(t_shell *shell, t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp && temp->type != 6)
	{
		if (temp->type >= 1 && temp->type <= 3)
		{
			enqueue(&shell->front, &shell->rear, temp);
			temp = temp->next;
			temp->type = 5;
			enqueue(&shell->front, &shell->rear, temp);
		}
		temp = temp->next;
	}
}

bool	is_syntax_error(t_shell *shell, t_token *token)
{
	if (token->type == PIPE)
	{
		if (token->next == NULL || token->next->type == PIPE)
		{
			token->type = SYNTAX_ERROR;
			ft_putendl_fd("Minishell: syntax error near unexpected token `|'", 2);
			return (true);
		}
	}
	if (token->type >= 0 && token->type <= 3)
	{
		if (token->next == NULL || token->next->type != 7)
		{
			token->type = SYNTAX_ERROR;
			if (token->next != NULL)
			{
				ft_putstr_fd("Minishell: ", 2);
				ft_putstr_fd("syntax error near unexpected token `", 2);
				ft_putstr_fd(token->next->str, 2);
				ft_putendl_fd("'", 2);
			}
			else
				ft_putendl_fd("Minishell: syntax error near unexpected token `newline'", 2);
			return (true);
		}
	}
	return (false);
}
