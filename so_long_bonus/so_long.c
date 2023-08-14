/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:49:01 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/01 19:56:49 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_env	env;

	init_struct(&env);
	check_arg(ac, av[1]);
	env.mlx.mlx = mlx_init();
	if (!env.mlx.mlx)
		return (1);
	if (!map(&env, av[1]))
		return (free_struct(&env), 0);
	init_info(&env);
	get_map_size(&env);
	if (!init_map(&env))
		return (free_struct(&env), 0);
	if (!verif_map(&env))
		return (free_struct(&env), 0);
	if (!init_minimap(&env))
		return (free_struct(&env), 0);
	set_hooks_mlx(&env);
	mlx_loop(env.mlx.mlx);
}
