#include "../../include/minishell.h"

bool	is_output_redirection(t_token **token, char **input)
{
	char	*str;

	if ((*input)[0] == '>' && (*input)[1] != '>')
	{
		*input += 1;
		ft_isspace(input);
		if ((*input)[0] == '\0')
			printf("syntax error near unexpected token `newline'\n");
		else
		{
			add_token_node(token, OUTPUT_R, ">");
			if ((*input)[0] == '\'' || (*input)[0] == '\"')
				add_token_node(token, FILENAME, quoted_word(input));
			else
				add_token_node(token, FILENAME, non_quoted_word(input));
		}
		return (true);
	}
	return (false);
}

bool	is_input_redirection(t_token **token, char **input)
{
	char	*str;

	if ((*input)[0] == '<' && (*input)[1] != '<')
	{
		*input += 1;
		ft_isspace(input);
		if ((*input)[0] == '\0')
			printf("syntax error near unexpected token `newline'\n");
		else
		{
			add_token_node(token, INPUT_R, "<");
			if ((*input)[0] == '\'' || (*input)[0] == '\"')
				add_token_node(token, FILENAME, quoted_word(input));
			else
				add_token_node(token, FILENAME, non_quoted_word(input));
		}
		return (true);
	}
	return (false);
}

bool	is_output_redirection_append(t_token **token, char **input)
{
	char	*str;

	if ((*input)[0] == '>' && (*input)[1] == '>')
	{	
		*input += 2;
		ft_isspace(input);
		if ((*input)[0] == '\0')
			printf("syntax error near unexpected token `newline'\n");
		else
		{
			add_token_node(token, OUTPUT_R_APPEND, ">>");
			if ((*input)[0] == '\'' || (*input)[0] == '\"')
				add_token_node(token, FILENAME, quoted_word(input));
			else
				add_token_node(token, FILENAME, non_quoted_word(input));
		}
		return (true);
	}
	return (false);
}
