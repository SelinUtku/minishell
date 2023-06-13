// bool	is_word(t_shell *shell)
// {
// 	char	*str;

// 	if (shell->input[shell->i] != '\0' && ft_strchr(SYMBOLS, shell->input[shell->i]) == 0)
// 	{
// 		if (shell->input[shell->i] == '\'' || shell->input[shell->i] == '\"')
// 		{
// 			str = quoted_word(shell);
// 			if (!str)
// 			{
// 				add_token_node(shell, SYNTAX_ERROR, str);
// 				return (false);
// 			}
// 			else if (shell->input[shell->i] == '\0' || ft_strchr(SYMBOLS, shell->input[shell->i]) != 0 || shell->input[shell->i] == ' ')
// 				add_token_node(shell, WORD, str);
// 			else
// 			{
// 				if (shell->input[shell->i] == '\'' || shell->input[shell->i] == '\"')
// 				{
// 					str = ft_strjoin(str, quoted_word(shell));
// 					if (shell->input[shell->i] == '\0' || ft_strchr(SYMBOLS, shell->input[shell->i]) != 0 || shell->input[shell->i] == ' ')
// 						add_token_node(shell, WORD, str);
// 				}
// 			}
// 		}
// 		else
// 		{
// 			str = non_quoted_word(shell);
// 			if (shell->input[shell->i] == '\'' || shell->input[shell->i] == '\"')
// 			{
// 				str = ft_strjoin(str, quoted_word(shell));
// 				if (shell->input[shell->i] == '\0' || ft_strchr(SYMBOLS, shell->input[shell->i]) != 0 || shell->input[shell->i] == ' ')
// 					add_token_node(shell, WORD, str);
// 			}
// 			else
// 				add_token_node(shell, WORD, str);
// 		}
// 	}
// 	return (true);
// }

// bool	is_heredoc(t_shell *shell)
// {
// 	char	*str;

// 	if (shell->input[shell->i] == '<' && shell->input[shell->i + 1] == '<')
// 	{	
// 		shell->i += 2;
// 		ft_isspace(shell);
// 		if (shell->input[shell->i] == '\0' || ft_strchr(SYMBOLS, shell->input[shell->i]) != 0)
// 		{
// 			str = my_malloc(&shell->garbage, 2, sizeof(char));
// 			str[0] = shell->input[shell->i];
// 			str[1] = '\0';
// 			add_token_node(shell, SYNTAX_ERROR, str);
// 			return (false);
// 		}
// 		else
// 		{
// 			add_token_node(shell, HEREDOC, "<<");
// 			if (shell->input[shell->i] == '\'' || shell->input[shell->i] == '\"')
// 				add_token_node(shell, DELIMITER, quoted_word(shell));
// 			else
// 				add_token_node(shell, DELIMITER, non_quoted_word(shell));
// 		}
// 	}
// 	return (true);
// }

// char	*quoted_word(t_shell *shell)
// {
// 	char	quote;
// 	char	*str;
// 	int		j;

// 	quote = shell->input[shell->i];
// 	j = shell->i + 1;
// 	while (shell->input[j] != quote && shell->input[j] != '\0')
// 		j++;
// 	if (j == shell->i + 1)
// 		return (NULL);
// 	str = ft_substr(shell->input, shell->i + 1, j - 1 - shell->i); //my_malloc degil
// 	shell->i = j;
// 	if (shell->input[shell->i] == '\0')
// 	{
// 		printf("Unclosed quote syntax error\n");
// 		return (NULL);
// 	}
// 	else
// 		shell->i += 1;
// 	return (str);
// }

// char	*non_quoted_word(t_shell *shell)
// {
// 	char	*str;
// 	int		j;

// 	j = shell->i;
// 	while (shell->input[j] != ' ' && ft_strchr(SYMBOLS, shell->input[j]) == 0 && shell->input[j] != '\0' \
// 	&& shell->input[j] != '\"' && shell->input[j] != '\'')
// 		j++;
// 	// if (j == shell->i)
// 	// 	return (NULL);
// 	str = ft_substr(shell->input, shell->i, j - shell->i);//my_malloc degil
// 	shell->i = j;
// 	return (str);
// }

// bool	is_input_redirection(t_shell *shell)
// {
// 	char	*str;

// 	if (shell->input[shell->i] == '<' && shell->input[shell->i + 1] != '<')
// 	{
// 		shell->i++;
// 		ft_isspace(shell);
// 		if (shell->input[shell->i] == '\0' || ft_strchr(SYMBOLS, shell->input[shell->i]) != 0)
// 		{
// 			str = my_malloc(&shell->garbage, 2, sizeof(char));
// 			str[0] = shell->input[shell->i];
// 			str[1] = '\0';
// 			add_token_node(shell, SYNTAX_ERROR, str);
// 			return (false);
// 		}
// 		else
// 		{
// 			add_token_node(shell, INPUT_R, "<");
// 			if (shell->input[shell->i] == '\'' || shell->input[shell->i] == '\"')
// 				add_token_node(shell, FILENAME, quoted_word(shell));// quoted dan dolayi i arttiginda baslangicini degil sonunu aliyoruz
// 			else
// 				add_token_node(shell, FILENAME, non_quoted_word(shell));
// 		}
// 	}
// 	return (true);
// }

// bool	is_output_redirection_append(t_shell *shell)
// {
// 	char	*str;

// 	if (shell->input[shell->i] == '>' && shell->input[shell->i + 1] == '>')
// 	{	
// 		shell->i += 2;
// 		ft_isspace(shell);
// 		if (shell->input[shell->i] == '\0' || ft_strchr(SYMBOLS, shell->input[shell->i]) != 0)
// 		{
// 			str = my_malloc(&shell->garbage, 2, sizeof(char));
// 			str[0] = shell->input[shell->i];
// 			str[1] = '\0';
// 			add_token_node(shell, SYNTAX_ERROR, str);
// 			return (false);
// 		}
// 		else
// 		{
// 			add_token_node(shell, OUTPUT_R_APPEND, ">>");
// 			if (shell->input[shell->i] == '\'' || shell->input[shell->i] == '\"')
// 				add_token_node(shell, FILENAME, quoted_word(shell));
// 			else
// 				add_token_node(shell, FILENAME, non_quoted_word(shell));
// 		}
// 	}
// 	return (true);
// }

// bool	is_output_redirection(t_shell *shell)
// {
// 	char	*str;

// 	if (shell->input[shell->i] == '>' && shell->input[shell->i + 1] != '>')
// 	{
// 		shell->i++;
// 		ft_isspace(shell);
// 		if (shell->input[shell->i] == '\0' || ft_strchr(SYMBOLS, shell->input[shell->i]) != 0)
// 		{
// 			str = my_malloc(&shell->garbage, 2, sizeof(char));
// 			str[0] = shell->input[shell->i];
// 			str[1] = '\0';
// 			add_token_node(shell, SYNTAX_ERROR, str);
// 			return (false);
// 		}
// 		else
// 		{
// 			add_token_node(shell, OUTPUT_R, ">");
// 			if (shell->input[shell->i] == '\'' || shell->input[shell->i] == '\"')
// 				add_token_node(shell, FILENAME, quoted_word(shell));
// 			else
// 				add_token_node(shell, FILENAME, non_quoted_word(shell));
// 		}
// 	}
// 	return (true);
// }

// bool	is_pipe(t_shell *shell)
// {
// 	char	*str;

// 	if (shell->input[shell->i] == '|')
// 	{
// 		shell->i++;
// 		ft_isspace(shell);
// 		if (shell->input[shell->i] == '\0')
// 		{
// 			add_token_node(shell, PIPE, "|");
// 			str = readline("> ");
// 			shell->input = ft_strjoin(shell->input, str);
// 			free(str);
// 			// ya tekrar pipe verirsem
// 		}
// 		else if (shell->input[shell->i] == '|')
// 		{
// 			add_token_node(shell, SYNTAX_ERROR, "|");
// 			return (false);
// 		}
// 		else
// 			add_token_node(shell, PIPE, "|");
// 	}
// 	return (true);
// }
