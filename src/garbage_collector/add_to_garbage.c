

#include "../../include/minishell.h"

void	add_garbage(t_garbage **first, void *ptr)
{
	t_garbage	*new;
	t_garbage	*last;

	new = (t_garbage *)malloc(sizeof(t_garbage));
	if (!new)
	{
		perror("malloc fail");
		exit (EXIT_FAILURE);
	}
	new->ptr = ptr;
	new->next = NULL;
	if (*first == NULL)
		*first = new;
	else
	{
		last = *first;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}