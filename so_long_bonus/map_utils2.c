/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:26:44 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/20 19:32:52 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_map(t_env *env)
{
	t_index	index;
	int		tmp_x;
	int		tmp_y;

	get_start_map(&index, env);
	tmp_x = env->map.p_x - (index.x_start);
	tmp_y = env->map.p_y - (index.y_start);
	copy_map(&env->map.full_map[index.y_start * \
	(env->map.size_line * IMG) + index.x_start], \
	env->map.win_map, *env);
	img_cpy(env->img.perso, &env->map.win_map[tmp_y * env->mlx.win_x + tmp_x], \
	env->mlx.win_x / IMG, 0);
	if (env->minimap.active)
	{
		copy_minimap(*env, env->minimap.minimap, env->map.win_map);
		print_mini_player(*env);
	}
	mlx_put_image_to_window(env->mlx.mlx, \
	env->mlx.mlx_win, env->img.mlx_img, 0, 0);
}

void	copy_map(int *all_map, int *win_map, t_env env)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = env.mlx.win_x * env.mlx.win_y;
	while (i < size)
	{
		win_map[i] = all_map[j];
		if (j == (env.mlx.win_x) - 1)
		{
			j = 0;
			all_map += (env.map.size_line * IMG);
		}
		else
			j++;
		i++;
	}
}

void	init_full_map(t_env *env)
{
	t_iter	iter;

	iter.count = 0;
	iter.j = 0;
	iter.c = 0;
	iter.map = env->map.all_map;
	//set_map(env->map.full_map, env->map.size_line * IMG, \
	//IMG * env->map.size_line, IMG * env->map.height);
	while (iter.map[iter.j])
	{
		iter.i = 0;
		while (iter.map[iter.j][iter.i] && iter.map[iter.j][iter.i] != '\n')
		{
			set_ptr(env, iter, &iter.c);
			iter.count++;
			iter.i++;
		}
		iter.j++;
	}
}

void	set_ptr(t_env *env, t_iter iter, int *c)
{
	if (iter.map[iter.j][iter.i] == '2')
		return ;
	if (iter.map[iter.j][iter.i] == '1')
		img_cpy(env->img.wall, &env->map.full_map[iter.count * IMG], \
		env->map.size_line, iter.j);
	if (iter.map[iter.j][iter.i] == '0' || iter.map[iter.j][iter.i] == 'P')
		img_cpy(env->img.floor, &env->map.full_map[iter.count * IMG], \
		env->map.size_line, iter.j);
	else if (iter.map[iter.j][iter.i] == 'E')
		img_cpy(env->img.exit, &env->map.full_map[iter.count * IMG], \
		env->map.size_line, iter.j);
	else if (iter.map[iter.j][iter.i] == 'C')
	{
		img_cpy(env->img.objet, &env->map.full_map[(env->map.objets[*c].y * \
		(env->map.size_line * IMG)) + \
		env->map.objets[*c].x], env->map.size_line, 0);
		(*c)++;
	}
}

void	set_map(int *ptr, int size_line, int size_img_line, int nb_img_line)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (j < nb_img_line)
	{
		i = 0;
		while (i < size_img_line)
		{
			ptr[size_line * j + i] = FLOOR;
			i++;
		}
		j++;
	}
}
