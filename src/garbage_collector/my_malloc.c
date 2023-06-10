

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
