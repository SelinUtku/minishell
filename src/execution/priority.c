#include "../../include/minishell.h"


void	exec_order(t_shell *shell)
{
	t_token	*temp;

	temp = shell->token;
	shell->front = NULL;
	shell->rear = NULL;
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
	if (token->type >= 0 && token->type <= 3)
	{
		if (token->next == NULL || token->next->type != 7)
		{
			if (token->next != NULL)
				printf("syntax error near unexpected token '%s'\n", token->next->str);
			else
				printf("syntax error near unexpected token 'newline'\n");
			return (true);
		}
	}
	return (false);
}

// void	here_doc(char *delimiter)
// {
// 	char *line;
// 	line = readline("> ");
// 	if (line == NULL || line[0] == EOF || \
// 	ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
// 	&& ft_strlen(line) == ft_strlen(delimiter))
// 	{
// 		free(line);
// 		return ;
// 	}
// 	else
// 	{
// 		write()
// 	}
// }