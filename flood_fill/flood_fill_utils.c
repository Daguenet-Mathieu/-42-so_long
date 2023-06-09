
#include "flood_fill.h"

t_fill	*init_fill(int x, int y)
{
	t_fill	*new;

	new = malloc(sizeof(t_fill));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	new->top = 0;
	new->down = 0;
	new->right = 0;
	new->left = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_to_fill(t_fill *new, t_fill **last_fill)
{
	if (!new)
		return ;
	if (!*last_fill)
	{
		*last_fill = new;
		return ;
	}
	(*last_fill)->next = new;
	new->prev = *last_fill;
	*last_fill = new;
}

void	init_coordonnees(t_fill **last_fill, int sens, int *x, int *y)
{
	*x = (*last_fill)->x;
	*y = (*last_fill)->y;
	if (sens == TOP)
	{
		(*last_fill)->top = 1;
		*y = *y - 1;
	}
	else if (sens == DOWN)
	{
		(*last_fill)->down = 1;
		*y = *y + 1;
	}
	else if (sens == LEFT)
	{
		(*last_fill)->left = 1;
		*x = *x - 1;
	}
	else if (sens == RIGHT)
	{
		(*last_fill)->right = 1;
		*x = *x + 1;
	}
}

void	free_fill(t_fill **last_fill)
{
	t_fill	*tmp;

	if (!*last_fill)
		return ;
	tmp = (*last_fill)->prev;
	free(*last_fill);
	if (tmp)
		tmp->next = NULL;
	*last_fill = tmp;
}