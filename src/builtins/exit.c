/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 03:14:28 by Cutku             #+#    #+#             */
/*   Updated: 2023/06/19 03:18:36 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(t_shell *shell)
{
	if (shell->input == NULL || shell->input[0] == EOF || \
	(ft_strncmp(shell->input, "exit", 4) == 0 && ft_strlen(shell->input) == 4))
	{
		free(shell->input);
		exit(EXIT_SUCCESS);
	}
}
