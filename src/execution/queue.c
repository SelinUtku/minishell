#include "../../include/minishell.h"

void	enqueue(t_queue **front, t_queue **rear, void *ptr)
{
	t_queue	*new;

	new = NULL;
	new = (t_queue *)malloc(sizeof(t_queue));
	if (!new)
	{
		perror ("malloc");
		exit (EXIT_FAILURE);
	}
	new->content = ptr;
	new->next = NULL;
	if (*front == NULL)
	{
		*front = new;
		*rear = new;
	}
	else
	{
		(*rear)->next = new;
		*rear = new;
	}
}

void	dequeue(t_queue **front)
{
	t_queue	*temp;

	if (*front != NULL)
	{
		temp = *front;
		*front = (*front)->next;
		free(temp);
	}
	else
		ft_putstr_fd("Queue is empty.\n", 2);
}