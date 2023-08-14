/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:24:38 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/01 19:40:16 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	do_move(t_pos pos, t_env *env, int *player, int new_pos)
{
	check(env, pos, 'C');
	*player = new_pos;
}

void	init_pos_l_r(t_pos *pos, t_env *env, int *move)
{
	pos->x = env->map.p_x;
	pos->y = env->map.p_y;
	pos->new_x = pos->x;
	pos->new_y = pos->y;
	if (env->key.right)
	{
		pos->new_x = pos->x + SPEED;
		*move += 1;
	}
	if (env->key.left)
	{
		pos->new_x = pos->x - SPEED;
		*move += 1;
	}
}

void	init_pos_t_d(t_pos *pos, t_env *env, int *move)
{
	pos->x = env->map.p_x;
	pos->y = env->map.p_y;
	pos->new_x = pos->x;
	pos->new_y = pos->y;
	if (env->key.down)
	{
		pos->new_y = pos->y + SPEED;
		*move += 1;
	}
	if (env->key.up)
	{
		pos->new_y = pos->y - SPEED;
		*move += 1;
	}
}
