/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 03:08:05 by sutku             #+#    #+#             */
/*   Updated: 2023/07/22 00:46:02 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_termios(t_shell *shell)
{
	struct termios	new_termios;

	tcgetattr(STDOUT_FILENO, &shell->termios);
	new_termios = shell->termios;
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &new_termios);
}

void	handle_signal_int(int signum)
{
	if (signum == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}


void	signals_child(t_shell *shell)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}


void	signals(t_shell *shell)
{
	struct sigaction	sig_int;

	setup_termios(shell);
	sig_int.sa_handler = &handle_signal_int;
	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_int, NULL);
	signal(SIGQUIT, SIG_IGN);
}
