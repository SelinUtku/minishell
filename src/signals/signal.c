/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 03:08:05 by sutku             #+#    #+#             */
/*   Updated: 2023/07/21 03:43:45 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// void	handle_sigint(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		ioctl(STDIN_FILENO, TIOCSTI, "\n");
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 	}
// }


// void	setup_termios(t_shell *shell)
// {
// 	struct termios	new_termios;

// 	tcgetattr(0, &shell->termios);// it stores current trminal settings.
// 	new_termios = shell->termios;
// 	new_termios.c_lflag &= ~ECHOCTL;// Specifically, it disables the display of control characters (ECHOCTL) in the terminal. Control characters are non-printable characters like backspace, delete, etc
// 	tcsetattr(0, TCSANOW, &new_termios);//is line sets the modified new_termios settings as the new terminal attributes.
// }

// void	handle_signal_int(int signum)
// {
// 	if (signum == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		return ;
// 	}
// }

// void	signals(t_shell *shell)
// {
// 	struct sigaction	sig_int;

// 	setup_termios(shell);
// 	sig_int.sa_handler = &handle_signal_int;
// 	sigemptyset(&sig_int.sa_mask);
// 	sig_int.sa_flags = SA_RESTART;
// 	sigaction(SIGINT, &sig_int, NULL);
// 	signal(SIGQUIT, SIG_IGN);// quitte sadece ignore etmeliyiz
// }

