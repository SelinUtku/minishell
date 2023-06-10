#include "../../include/minishell.h"

void	add_token_node(t_token **token, t_type type, char *str)
{
	t_token	*new;
	t_token	*last;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->type = type;
	new->str = str;
	if (*token == NULL)
	{
		new->prev = NULL;
		new->next = NULL;
		*token = new;
	}
	else
	{
		last = *token;
		while (last->next != NULL)
			last = last->next;
		new->prev = last;
		new->next = NULL;
		last->next = new;
	}
}

void	split_pipes(t_token **token, char **input)
{
	char	**splitted_input;
	int		i;

	splitted_input = ft_split(*input, '|');
	i = 0;
	while (splitted_input[i] != NULL)
	{
		examine_type(token, &splitted_input[i]);
		i++;
		if (splitted_input[i] != NULL)
			add_token_node(token, PIPE, "|");
	}
}

void	examine_type(t_token **token, char **input)
{
	while (*input[0] != '\0')
	{
		if (ft_isspace(input))
			;
		else if (is_input_redirection(token, input))
			;
		else if (is_output_redirection(token, input))
			;
		else if (is_heredoc(token, input))
			;
		else if (is_output_redirection_append(token, input))
			;
		else
			is_word(token, input);
		// if (*input[0] != '\0')
		// 	*input += 1;
	}
}

bool	ft_isspace(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i] == ' ' && (*str)[i] != '\0')
		i++;
	*str += i;
	if (i != 0)
		return (true);
	return (false);
}

void	is_word(t_token **token, char **input)
{
	if ((*input)[0] == '\'' || (*input)[0] == '\"')
		add_token_node(token, WORD, quoted_word(input));
	else
		add_token_node(token, WORD, non_quoted_word(input));
}
