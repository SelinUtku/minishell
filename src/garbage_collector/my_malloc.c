/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 04:48:26 by Cutku             #+#    #+#             */
/*   Updated: 2023/07/06 04:48:36 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*my_malloc(t_garbage **garbage, size_t count, size_t size)
{
	void	*ptr;

	if (count != 0 && ((size * count) / count != size))
	{
		perror("malloc fail");
		clean_garbage(garbage);
		exit (EXIT_FAILURE);
	}
	ptr = malloc(count * size);
	if (!ptr)
	{
		perror("malloc fail");
		clean_garbage(garbage);
		exit (EXIT_FAILURE);
	}
	add_garbage(garbage, ptr);
	return (ptr);
}
