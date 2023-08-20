/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:26:47 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/20 19:35:25 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	img_cpy(t_img img, int *ptr, int size_line, int nb_line)
{
	int	i;
	int	j;

	ptr += (nb_line * IMG) * ((size_line * (IMG - 1)));
	i = 0;
	j = 0;
	while (i < img.size)
	{
		if (img.img[i] != (int)TRANSPARENT)
			ptr[j] = img.img[i];
		if (j == img.width - 1)
		{
			j = 0;
			ptr += (size_line) * IMG;
		}
		else
			j++;
		i++;
	}
}

void	set_x_start(t_index *index, t_env *env)
{
	int	player_x;
	int	player_y;

	player_x = env->map.p_x;
	player_y = env->map.p_y;
	if (player_x <= (env->mlx.win_x) / 2)
	{
		index->x_start = 0;
		index->x_end = (env->mlx.win_x);
	}
	else if (env->map.size_line * IMG - player_x <= (env->mlx.win_x) / 2)
	{
		index->x_end = env->map.size_line * IMG;
		index->x_start = index->x_end - (env->mlx.win_x);
	}
	else
	{
		index->x_start = player_x - (env->mlx.win_x) / 2;
		index->x_end = index->x_start + (env->mlx.win_x / IMG);
	}
}

void	set_y_start(t_index *index, t_env *env)
{
	int	player_x;
	int	player_y;

	player_x = env->map.p_x;
	player_y = env->map.p_y;
	if (player_y <= (env->mlx.win_y) / 2)
	{
		index->y_start = 0;
		index->y_end = (env->mlx.win_y);
	}
	else if (env->map.height * IMG - player_y <= (env->mlx.win_y) / 2)
	{
		index->y_end = env->map.height * IMG;
		index->y_start = index->y_end - (env->mlx.win_y);
	}
	else
	{
		index->y_start = player_y - ((env->mlx.win_y) / 2);
		index->y_end = index->y_start + (env->mlx.win_y);
	}
}

void	get_start_map(t_index *index, t_env *env)
{
	set_x_start(index, env);
	set_y_start(index, env);
}

void	get_map_size(t_env *env)
{
	env->map.height = tab_size(env->map.all_map);
	env->map.size_line = ft_strlen(env->map.all_map[0]);
	mlx_get_screen_size(env->mlx.mlx, &env->mlx.screen_x, &env->mlx.screen_y);
	env->mlx.screen_y -= 125;
	env->mlx.win_x = env->map.size_line * IMG;
	env->mlx.win_y = env->map.height * IMG;
	if (env->mlx.screen_x < env->mlx.win_x)
		env->mlx.win_x = env->mlx.screen_x;
	if (env->mlx.screen_y < env->mlx.win_y)
		env->mlx.win_y = env->mlx.screen_y;
}
