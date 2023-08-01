/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:25:48 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/01 20:00:38 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_nb_move(t_env *env)
{
	char	c;
	int		i;
	int		size;
	int		nb;

	c = 8;
	i = 0;
	size = 11;
	nb = env->map.nb_move;
	while (nb > 9)
	{
		nb /= 10;
		size++;
	}
	while (i < size)
	{
		write(1, &c, 1);
		i++;
	}
	env->map.nb_move += 1;
	ft_putstr("nb move = ", 1);
	ft_putnbr(env->map.nb_move);
}

void	delete_obj(t_obj *obj, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		obj[i] = obj[i + 1];
		i++;
	}
}

void	remove_collectible(t_env *env, int i, int j)
{		
	int	c;
	int	s_l;
	int	*map;

	c = 0;
	s_l = env->map.size_line * IMG;
	map = env->map.full_map;
	while (c < env->map.nb_collectible)
	{
		if (env->map.objets[c].j == j && env->map.objets[c].i == i)
		{
			delete_obj(&env->map.objets[c], env->map.nb_collectible - c);
			env->map.nb_collectible -= 1;
			set_map(map + (j * IMG * (s_l) + (i * IMG)), s_l, IMG, IMG);
			set_map(env->minimap.minimap + (j * SIZE_MINIMAP * \
			(env->minimap.size_line * SIZE_MINIMAP) + (i * SIZE_MINIMAP)), \
			env->minimap.size_line * SIZE_MINIMAP, SIZE_MINIMAP, SIZE_MINIMAP);
		}
		c++;
	}
}
