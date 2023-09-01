/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:26:41 by madaguen          #+#    #+#             */
/*   Updated: 2023/09/01 21:16:36 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	verif_map(t_env *env)
{	
	char	**new_map;
	int		x;
	int		y;

	if (!verif_wall(env->map.all_map))
		return (ft_error("map must be surrounded by walls\n"), 0);
	new_map = cpy_map(env->map.all_map);
	if (!new_map)
		free_struct(env);
	get_player_pos(env->map.all_map, &x, &y);
	flood_fill(x, y, new_map);
	if (get_map_nb(new_map, 'C') || get_map_nb(new_map, 'E')
		|| !verif_char(env->map.all_map))
	{
		ft_error("invalid map\n");
		free_tab(new_map);
		free_struct(env);
	}
	free_tab(new_map);
	return (1);
}

int	init_map(t_env *env)
{
	int	endian;
	int	size_line;
	int	bpp;

	env->map.full_map = malloc(sizeof(int) * env->map.height * IMG
			* env->map.size_line * IMG);
	if (!env->map.full_map)
		free_struct(env);
	env->img.mlx_img = (int *)mlx_new_image(env->mlx.mlx, \
	env->mlx.win_x, env->mlx.win_y);
	if (!env->img.mlx_img)
		free_struct(env);
	env->map.win_map = (int *)mlx_get_data_addr(env->img.mlx_img, \
	&bpp, &size_line, &endian);
	if (!init_img(env))
		free_struct(env);
	env->map.objets = init_pos_obj(env->map.all_map, *env);
	if (!env->map.objets)
		free_struct(env);
	return (1);
}

int	map(t_env *env, char *arg)
{
	env->map.all_map = get_map(arg);
	if (!env->map.all_map)
		free_struct(env);
	return (1);
}

void	init_objs_util(t_obj *objs, t_iter *it, t_env env)
{
	objs[it->c].x = (it->i * IMG) + ((IMG / 2) - (env.img.objet.width / 2));
	objs[it->c].y = (it->j * IMG) + ((IMG / 2) - \
	(env.img.objet.height / 2));
	objs[it->c].i = it->i;
	objs[it->c].j = it->j;
	(it->c)++;
}

t_obj	*init_pos_obj(char **map, t_env env)
{
	int		size;
	t_iter	it;
	t_obj	*objs;

	size = env.map.nb_collectible;
	it.j = 0;
	it.c = 0;
	objs = malloc(sizeof(t_obj) * size);
	while (objs && map[it.j])
	{
		it.i = 0;
		while (map[it.j][it.i] && map[it.j][it.i] != '\n')
		{
			if (map[it.j][it.i] == 'C')
				init_objs_util(objs, &it, env);
			it.i++;
		}
		it.j++;
	}
	return (objs);
}
