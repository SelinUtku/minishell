

#include "../../include/minishell.h"

void	del_one_from_garbage(t_garbage **first, void *ptr)
{
	t_garbage	*prev;
	t_garbage	*del;

	del = *first;
	prev = NULL;
	if ((*first)->ptr == ptr)
	{
		*first = (*first)->next;
		del_node(del);
	}
	else
	{
		while (del != NULL)
		{
			if (del->ptr == ptr)
			{
				prev->next = del->next;
				del_node(del);
				break ;
			}
			prev = del;
			del = del->next;
		}
	}
}

void	clean_garbage(t_garbage **first)
{
	t_garbage	*del;

	while (*first != NULL)
	{
		del = *first;
		*first = (*first)->next;
		del_node(del);
	}
}

void	del_node(t_garbage *del)
{
	free(del->ptr);
	free(del);
	del = NULL;
}
