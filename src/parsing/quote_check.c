#include "../../include/minishell.h"

//Unclosed quote possiblity ??
char	*quoted_word(char **input)
{
	char	quote;
	char	*str;
	int		i;

	quote = (*input)[0];
	i = 1;
	while ((*input)[i] != quote && (*input)[i] != '\0')
		i++;
	str = ft_substr(*input, 1, i - 1);
	*input += i;
	if ((*input)[0] == '\0')
	{
		printf("Unclosed quote syntax error\n");
		return (NULL);
	}
	else
		*input += 1;
	return (str);
}

char	*non_quoted_word(char **input)
{
	char	*str;
	int		i;

	i = 0;
	while ((*input)[i] != ' ' && (*input)[i] != '\0')
		i++;
	str = ft_substr(*input, 0, i);
	*input += i;
	return (str);
}
