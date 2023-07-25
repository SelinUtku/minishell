/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 04:02:59 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/25 21:20:59 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **env)
{
	if (argc != 1 && argv)
	{
		write (2, "Minishell does not take any arguments\n", 39);
		return (1);
	}
	else
		return (execute_minishell(env));
	return (0);
}

void	get_input_and_parse(t_shell *shell)
{
	shell->input = readline("MinisHELL$ ");
	if (shell->input == NULL || shell->input[0] == EOF)
	{
		clean_garbage(&shell->garbage);
		exit(g_exit_status);
	}
	add_history(shell->input);
	parse_the_input(shell);
}

void	parse_the_input(t_shell *shell)
{
	define_type(shell);
	exec_order(shell);
	is_expandable(shell);
	split_after_expand(shell);
	delete_quotes(shell);
}

int	execute_minishell(char **env)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		exit(EXIT_FAILURE);
	create_structure(shell, env);
	while (1)
	{
		init_shell_struct(shell);
		signals(shell);
		// get_input_and_parse(shell);
		if (isatty(fileno(stdin)))
			shell->input = readline("MinisHell$ ");
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			shell->input = ft_strtrim(line, "\n");
			free(line);
		}
		if (shell->input == NULL || shell->input[0] == EOF)
		{
			clean_garbage(&shell->garbage);
			exit(g_exit_status);
		}
		add_history(shell->input);
		parse_the_input(shell);
		here_doc(shell);
		shell->num_pipe = pipe_counter(shell);
		if (check_syntax_error(shell) == 0)
			exec_choice(shell);
		unlink_heredocs(shell);
		free(shell->input);
	}
	clean_garbage(&shell->garbage);
	return (g_exit_status);
}
