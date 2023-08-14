/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:25:45 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/01 19:54:16 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_minimap(t_env *env)
{
	env->minimap.active = 1;
	env->minimap.size_line = env->map.size_line;
	env->minimap.nb_line = env->map.height;
	env->minimap.minimap = malloc(sizeof(int) * env->minimap.size_line \
	* SIZE_MINIMAP * env->minimap.nb_line * SIZE_MINIMAP);
	if (!env->minimap.minimap)
		return (0);
	set_minimap(&env->minimap, env->map.all_map);
	return (1);
}
