#include "../../include/minishell.h"

bool	is_output_redirection(t_shell *shell)
{
	if (shell->input[shell->i] == '>' && shell->input[shell->i + 1] != '>')
	{
		add_token_node(shell, OUTPUT_R, ">");
		shell->i++;
		return (true);
	}
	return (false);
}

bool	is_input_redirection(t_shell *shell)
{
	if (shell->input[shell->i] == '<' && shell->input[shell->i + 1] != '<')
	{
		add_token_node(shell, INPUT_R, "<");
		shell->i++;
		return (true);
	}
	return (false);
}

bool	is_output_redirection_append(t_shell *shell)
{
	if (shell->input[shell->i] == '>' && shell->input[shell->i + 1] == '>')
	{
		add_token_node(shell, OUTPUT_R_APPEND, ">>");
		shell->i += 2;
		return (true);
	}
	return (false);
}
