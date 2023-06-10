

#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_type
{
	HEREDOC,
	DELIMITER,
	INPUT_R,
	OUTPUT_R,
	OUTPUT_R_APPEND,
	FILENAME,
	PIPE,
	WORD,

}t_type;

typedef struct s_token
{
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
	char			*str;
}t_token;

bool	ft_isspace(char **str);
bool	is_output_redirection(t_token **token, char **input);
bool	is_input_redirection(t_token **token, char **input);
char	*quoted_word(char **input);
char	*non_quoted_word(char **input);
void	examine_type(t_token **token, char **input);
void	add_token_node(t_token **token, t_type type, char *str);
void	is_word(t_token **token, char **input);
void	split_pipes(t_token **token, char **input);
bool	is_heredoc(t_token **token, char **input);
bool	is_output_redirection_append(t_token **token, char **input);


#endif