/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:26:56 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/20 21:48:14 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_img(t_env *env)
{
	init_struct_img(&env->img.wall, IMG, IMG);
	init_struct_img(&env->img.objet, IMG / 2, IMG / 2);
	init_struct_img(&env->img.exit, IMG, IMG);
	init_struct_img(&env->img.perso, HEIGHT_PLAYER, WIDTH_PLAYER);
	env->img.wall.img = init_square(WALL, env->img.wall.size);
	env->img.exit.img = init_square(EXIT, env->img.exit.size);
	env->img.perso.img = init_square(PLAYER, env->img.perso.size);
	env->img.objet.img = init_circle(OBJET, env->img.objet.height / 2);
	if (!env->img.wall.img || !env->img.exit.img || \
	!env->img.perso.img || !env->img.objet.img)
		return (free_struct(env), ft_error("fail malloc image\n"), 0);
	return (1);
}

void	free_struct(t_env *env)
{		
	(void) env;

	mlx_destroy_window(env->mlx.mlx, env->mlx.mlx_win);
	mlx_destroy_display(env->mlx.mlx);
	free_tab(env->map.all_map);
	//mlx_destroy_image(env->mlx.mlx, env->map.win_map);
	mlx_loop_end(env->mlx.mlx);
	free(env->mlx.mlx);
	free(env->img.wall.img);
	free(env->img.objet.img);
	free(env->img.exit.img);
	free(env->img.perso.img);
	free(env->minimap.minimap);
	exit(0);
}

int	mlx_close(t_env *env)
{
	(void) env;
	free_struct(env);
	return (0);
}

void	set_hooks_mlx(t_env *env)
{
	int	x;
	int	y;

	x = env->mlx.win_x;
	y = env->mlx.win_y;
	env->mlx.mlx_win = mlx_new_window(env->mlx.mlx, x, y, "so_long");
	init_full_map(env);
	load_map(env);
	if (!env->mlx.mlx_win)
	{
		free_struct(env);
		return ;
	}
	mlx_hook(env->mlx.mlx_win, 17, 0, mlx_close, env);
	mlx_hook(env->mlx.mlx_win, 3, 1 << 1, handle_keyrelease, env);
	mlx_hook(env->mlx.mlx_win, 2, 1L << 0, handle_keypress, env);
	mlx_loop_hook(env->mlx.mlx, &handle_key, env);
}
