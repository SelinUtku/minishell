#include "../../include/minishell.h"

bool	is_heredoc(t_shell *shell)
{
	if (shell->input[shell->i] == '<' && shell->input[shell->i + 1] == '<')
	{
		add_token_node(shell, HEREDOC, "<<");
		shell->i += 2;
		return (true);
	}
	return (false);
}
