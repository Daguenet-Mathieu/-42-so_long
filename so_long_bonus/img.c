/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:26:31 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/01 20:14:05 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*init_square(int color, int size)
{
	int	*ptr;
	int	i;

	i = 0;
	ptr = malloc(sizeof(int) * size);
	if (!ptr)
		return (NULL);
	while (i < size)
	{
			ptr[i] = color;
			i++;
	}
	return (ptr);
}

void	*init_circle(int color, int radius)
{
	int	*ptr;
	int	i;
	int	x;
	int	y;

	y = 0;
	i = 0;
	ptr = malloc(sizeof(int) * radius * 2 * radius * 2);
	while (ptr && y < radius * 2)
	{
		x = 0;
		while (x < radius * 2)
		{
			if (((x - radius) * (x - radius)) + ((y - radius) * (y - radius))
				<= (radius * radius))
				ptr[i] = color;
			else
				ptr[i] = TRANSPARENT;
			i++;
			x++;
		}
		y++;
	}
	return (ptr);
}

void	get_player_pos(char **map, int *x, int *y)
{
	int	i;
	int	j;
	int	player;

	player = 0;
	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == 'P')
			{
				player = 1;
				break ;
			}
			i++;
		}
		if (player)
			break ;
		j++;
	}
	*x = i;
	*y = j;
}
