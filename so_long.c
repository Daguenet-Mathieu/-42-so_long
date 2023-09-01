/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:49:01 by madaguen          #+#    #+#             */
/*   Updated: 2023/09/01 20:47:38 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_env	env;

	init_struct(&env);
	if (!check_arg(ac, av[1]))
		return (ft_error("only one parameter and map file should be .ber\n"),
			free_struct(&env), 0);
	env.mlx.mlx = mlx_init();
	if (!env.mlx.mlx)
		free_struct(&env);
	if (!map(&env, av[1]))
		free_struct(&env);
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
