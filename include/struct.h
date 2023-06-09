/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 02:59:18 by sutku             #+#    #+#             */
/*   Updated: 2023/06/09 03:47:53 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_type
{
	WORD,
	INPUT_FILE,
	OUTPUT_FILE,
	PIPE,
}t_type;

typedef struct s_token
{
	t_type			type;
	int				index;
	struct s_token	*prev;
	struct s_token	*next;
	char			*str;
}t_token;

#endif