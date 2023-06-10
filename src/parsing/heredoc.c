#include "../../include/minishell.h"

bool	is_heredoc(t_token **token, char **input)
{
	char	*str;

	if ((*input)[0] == '<' && (*input)[1] == '<')
	{	
		*input += 2;
		ft_isspace(input);
		if ((*input)[0] == '\0')
			printf("syntax error near unexpected token `newline'\n");
		else
		{
			add_token_node(token, HEREDOC, "<<");
			if ((*input)[0] == '\'' || (*input)[0] == '\"')
				add_token_node(token, DELIMITER, quoted_word(input));
			else
				add_token_node(token, DELIMITER, non_quoted_word(input));
		}
		return (true);
	}
	return (false);
}
