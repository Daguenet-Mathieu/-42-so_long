/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:24:41 by madaguen          #+#    #+#             */
/*   Updated: 2023/09/01 22:13:40 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ajust_key_release(int *key1, int *key2)
{
	if (*key1 == 2)
	*key2 = 1;
	else if (*key2 == 2)
		*key2 = 1;
	*key1 = 0;
}

int	handle_keyrelease(int key_code, t_env *env)
{
	if (key_code == 65363 || key_code == 100)
		ajust_key_release(&env->key.right, &env->key.left);
	else if (key_code == 65362 || key_code == 119)
		ajust_key_release(&env->key.up, &env->key.down);
	else if (key_code == 65361 || key_code == 97)
		ajust_key_release(&env->key.left, &env->key.right);
	else if (key_code == 65364 || key_code == 115)
		ajust_key_release(&env->key.down, &env->key.up);
	return (key_code);
}

void	ajust_key_press(int *key1, int *key2)
{
	if (*key2)
		*key1 = 2;
	else
		*key1 = 1;
	*key2 = 0;
}

int	handle_keypress(int key_code, t_env *env)
{
	if (key_code == 65307)
		return (write(1, "\n", 1), free_struct(env), 0);
	if (key_code == 101)
	{
		env->minimap.active = env->minimap.active ^ 1;
		load_map(env);
	}
	if (key_code == 65363 || key_code == 100)
		ajust_key_press(&env->key.right, &env->key.left);
	else if (key_code == 65362 || key_code == 119)
		ajust_key_press(&env->key.up, &env->key.down);
	else if (key_code == 65361 || key_code == 97)
		ajust_key_press(&env->key.left, &env->key.right);
	else if (key_code == 65364 || key_code == 115)
		ajust_key_press(&env->key.down, &env->key.up);
	return (key_code);
}

int	handle_key(t_env *env)
{
	t_pos	pos;
	int		move;
	int		check_move;

	move = 0;
	check_move = 0;
	init_pos_t_d(&pos, env, &check_move);
	if (!check(env, pos, '1') && check_move)
		move = do_move(pos, env, &env->map.p_y, pos.new_y);
	check_move = 0;
	init_pos_l_r(&pos, env, &check_move);
	if (!check(env, pos, '1') && check_move)
		move = do_move(pos, env, &env->map.p_x, pos.new_x);
	if (move)
	{	
		load_map(env);
		print_nb_move(env);
	}
	if (!env->map.nb_collectible && check(env, pos, 'E'))
		return (ft_putstr("\nEnd!\n", 1), free_struct(env), 0);
	return (0);
}
