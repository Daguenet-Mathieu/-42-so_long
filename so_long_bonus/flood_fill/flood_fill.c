#include "flood_fill.h"

int	check_fill(t_fill *fill)
{
	if (fill->top && fill->right && fill->left && fill->down)
		return (0);
	return (1);
}

void	clear_fill(t_fill **last_fill)
{
	while (last_fill)
		free_fill(last_fill);
}

void	check_direction(t_fill_env *fill)
{
	if (!fill->last_fill->top)
		init_coordonnees(&fill->last_fill, TOP, &fill->new_x, &fill->new_y);
	else if (!fill->last_fill->down)
		init_coordonnees(&fill->last_fill, DOWN, &fill->new_x, &fill->new_y);
	else if (!fill->last_fill->left)
		init_coordonnees(&fill->last_fill, LEFT, &fill->new_x, &fill->new_y);
	else if (!fill->last_fill->right)
		init_coordonnees(&fill->last_fill, RIGHT, &fill->new_x, &fill->new_y);
}

void	flood_fill(int x, int y, char **map)
{
	t_fill_env	fill;

	fill.last_fill = init_fill(x, y);
	while (fill.last_fill)
	{
		check_direction(&fill);
		if (map[fill.last_fill->y][fill.last_fill->x] != 'P'
			&& map[fill.last_fill->y][fill.last_fill->x] != '1')
			map[fill.last_fill->y][fill.last_fill->x] = 'F';
		fill.new = init_fill(fill.new_x, fill.new_y);
		if (!fill.new)
			return (/*ft_putstr("fail de malloc dans flood_map", 2), */
				clear_fill(&fill.last_fill));
		if (map[fill.new->y][fill.new->x] != 'F'
			&& map[fill.new->y][fill.new->x] != '1')
			add_to_fill(fill.new, &fill.last_fill);
		else
			free_fill(&fill.new);
		if (!check_fill(fill.last_fill))
			free_fill(&fill.last_fill);
	}
}
