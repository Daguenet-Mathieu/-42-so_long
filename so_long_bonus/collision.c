/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:25:50 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/01 19:59:04 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	in_case_y(t_pos pos, int c_y, int size)
{
	if (c_y >= pos.new_y && c_y < pos.new_y + HEIGHT_PLAYER)
		return (1);
	if (c_y + size > pos.new_y && c_y + size <= pos.new_y + HEIGHT_PLAYER)
		return (1);
	if (c_y <= pos.new_y && c_y + size > pos.new_y + HEIGHT_PLAYER)
		return (1);
	return (0);
}

int	player_in_case(t_pos pos, t_case this_case, int pixel)
{
	int	c_x;
	int	c_y;
	int	size;

	c_x = this_case.x * IMG + pixel;
	c_y = this_case.y * IMG + pixel;
	size = IMG - (pixel * 2);
	if (c_x > pos.new_x && c_x < pos.new_x + WIDTH_PLAYER)
	{
		if (in_case_y(pos, c_y, size))
			return (1);
	}
	if (c_x + size > pos.new_x && c_x + size <= pos.new_x + WIDTH_PLAYER)
	{
		if (in_case_y(pos, c_y, size))
			return (1);
	}
	if (c_x <= pos.new_x && c_x + size > pos.new_x + WIDTH_PLAYER)
	{
		if (in_case_y(pos, c_y, size))
			return (1);
	}
	return (0);
}

int	verif_case(t_env *env, t_pos pos, char c, t_case this_case)
{
	int	pixel;

	pixel = 0;
	if (c == 'E')
		pixel = IMG / 2;
	if (c == 'C')
		pixel = IMG / 4;
	if (player_in_case(pos, this_case, pixel) \
		&& env->map.all_map[this_case.y][this_case.x] == c)
	{
		if (c == 'C')
		{
			remove_collectible(env, this_case.x, this_case.y);
			env->map.all_map[this_case.y][this_case.x] = '0';
		}
		return (1);
	}
	return (0);
}

void	init_zone(t_case zone[4], t_pos pos)
{
	zone[0].x = pos.new_x / IMG;
	zone[1].x = pos.new_x / IMG + 1;
	zone[2].x = pos.new_x / IMG;
	zone[3].x = pos.new_x / IMG + 1;
	zone[0].y = pos.new_y / IMG;
	zone[1].y = pos.new_y / IMG;
	zone[2].y = pos.new_y / IMG + 1;
	zone[3].y = pos.new_y / IMG + 1;
}

int	check(t_env *env, t_pos pos, char c)
{
	t_case	zone[4];

	init_zone(zone, pos);
	if (verif_case(env, pos, c, zone[0]))
		return (1);
	if (verif_case(env, pos, c, zone[1]))
		return (1);
	if (verif_case(env, pos, c, zone[2]))
		return (1);
	if (verif_case(env, pos, c, zone[3]))
		return (1);
	return (0);
}
