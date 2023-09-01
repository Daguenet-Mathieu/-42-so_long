/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:26:01 by madaguen          #+#    #+#             */
/*   Updated: 2023/09/01 21:14:46 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_struct(t_env *env)
{
	int		i;
	int		size;
	char	*tmp_env;

	size = sizeof(t_env);
	i = 0;
	tmp_env = (char *) env;
	while (i < size)
	{
		tmp_env[i] = 0;
		i++;
	}
}

void	init_struct_img(t_img *img, int height, int width)
{
	img->size = height * width;
	img->height = height;
	img->width = width;
}

int	check_arg(int size, char *arg)
{
	if (size != 2)
		return (0);
	if (!check_map_name(arg, ".ber"))
		return (0);
	return (1);
}

void	init_info(t_env *env)
{
	env->map.nb_move = 0;
	env->map.nb_collectible = get_map_nb(env->map.all_map, 'C');
	if (!env->map.nb_collectible)
		return (ft_error("la map should contain object\n"), free_struct(env));
	if (get_map_nb(env->map.all_map, 'P') != 1)
		return (ft_error("map should contain 1 player\n"), free_struct(env));
	if (get_map_nb(env->map.all_map, 'E') == 0)
		return (ft_error("map should contain an exit\n"), free_struct(env));
	get_player_pos(env->map.all_map, &env->map.p_x, &env->map.p_y);
	env->map.p_x = env->map.p_x * IMG + (IMG / 2 - WIDTH_PLAYER / 2);
	env->map.p_y = env->map.p_y * IMG + (IMG / 2 - HEIGHT_PLAYER / 2);
}
