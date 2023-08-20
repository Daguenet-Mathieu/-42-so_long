/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:25:46 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/20 21:03:14 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_mini_player(t_env env)
{
	int	p_x;
	int	p_y;

	p_x = env.map.p_x / IMG;
	p_y = env.map.p_y / IMG;
	fill_minimap(PLAYER, env.map.win_map + (p_x * SIZE_MINIMAP + \
	(p_y * SIZE_MINIMAP * env.mlx.win_x)), env.mlx.win_x, SIZE_MINIMAP);
}

void	copy_minimap(t_env env, int *minimap, int *map)
{
	int	i;
	int	j;
	int	minimap_size;

	minimap_size = env.minimap.size_line * SIZE_MINIMAP * \
	env.minimap.nb_line * SIZE_MINIMAP;
	i = 0;
	j = 0;
	while (i < minimap_size)
	{
		if ((unsigned int)minimap[i] != TRANSPARENT)
			map[j] = minimap[i];
		i++;
		if (j == env.minimap.size_line * SIZE_MINIMAP - 1)
		{
			j = 0;
			map += env.mlx.win_x;
		}
		else
			j++;
	}
}

void	fill_minimap(int color, int	*map, int size_line, int width)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (c < SIZE_MINIMAP * width)
	{
		map[i] = color;
		i++;
		c++;
		if (i == width)
		{
			map += (size_line);
			i = 0;
		}
	}
}

void	set_minimap_util(t_minimap *minimap, char **map, int i, int j)
{
	int	size_line;

	size_line = minimap->size_line;
	if (map[j][i] == '1')
		fill_minimap(WALL, minimap->minimap + (i * SIZE_MINIMAP + \
		(j * SIZE_MINIMAP * size_line * SIZE_MINIMAP)), \
		minimap->size_line * SIZE_MINIMAP, SIZE_MINIMAP);
	else if (map[j][i] == 'E')
		fill_minimap(EXIT, minimap->minimap + (i * SIZE_MINIMAP + \
		(j * SIZE_MINIMAP * size_line * SIZE_MINIMAP)), \
		minimap->size_line * SIZE_MINIMAP, SIZE_MINIMAP);
	else if (map[j][i] == 'C')
		fill_minimap(OBJET, minimap->minimap + (i * SIZE_MINIMAP + \
		(j * SIZE_MINIMAP * size_line * SIZE_MINIMAP)), \
		minimap->size_line * SIZE_MINIMAP, SIZE_MINIMAP);
	else if (map[j][i] == '2')
		fill_minimap(TRANSPARENT, minimap->minimap + (i * SIZE_MINIMAP + (j * SIZE_MINIMAP * size_line * SIZE_MINIMAP)),	minimap->size_line * SIZE_MINIMAP, SIZE_MINIMAP);
	else
		fill_minimap(FLOOR, minimap->minimap + (i * SIZE_MINIMAP + \
		(j * SIZE_MINIMAP * size_line * SIZE_MINIMAP)), \
		minimap->size_line * SIZE_MINIMAP, SIZE_MINIMAP);
}

void	set_minimap(t_minimap *minimap, char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i] && map[j][i] != '\n')
		{
			set_minimap_util(minimap, map, i, j);
			i++;
		}
		j++;
	}
}
