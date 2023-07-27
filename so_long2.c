/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:49:01 by madaguen          #+#    #+#             */
/*   Updated: 2023/04/22 21:29:16 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_putnbr(int n)
{
	unsigned int	nb;
	char			c;

	if (n < 0 && write(1, "-", 1))
		n = n * -1;
	nb = n;
	if (n >= 10)
		ft_putnbr(n/10);
	c = nb % 10 + 48;

	write(1, &c, 1);
}

int	lst_size(t_list *a)
{
	int	i;
	
	i = 0;
	while (a)
	{
		a = a->next;
		i++;
	}
	return (i);
}

int	ft_strlen(char *s)
{
	int	i;
	
	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	tab_size(char **map)
{
	int	i;
	
	i = 0;
	while (map && map[i])
		i++;
	return (i);
}

t_list	*lst_new(char *s)
{
	t_list	*new;
	
	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = s;
	new->next = NULL;
	return (new);
}

char	**convert_list(t_list **tmp_map)
{
	char	**map;
	int	size;
	int	i;
	t_list	*tmp;
	
	i = 0;
	size = lst_size(*tmp_map);
	map = malloc(sizeof(char*) * size);
	if (!map)
		return (NULL);
	while (i < size)
	{
		map[i] = (*tmp_map)->content;
		i++;
		tmp = (*tmp_map)->next;
		free(*tmp_map);
		*tmp_map = tmp;
	}
	return (map);
}

void	add_back(t_list **list, t_list *new)
{
	t_list	*tmp;
	
	tmp = *list;
	if (!*list)
	{
		*list = new;
		return ;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	ft_putstr(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	ft_error(char *s)
{
	ft_putstr(s, 2);
}

char	**cpy_map(char **map)
{
	char	**new_map;
	int		i;
	int	j;

	j = 0;
	new_map = malloc(sizeof(char *) * (tab_size(map) + 1));
	if (!new_map)
		return (ft_error("fail malloc cpy ;ap\n"), NULL);
	while (map[j])
	{
		i = 0;
		new_map[j] = malloc(ft_strlen(map[j] + 1));
		if (!new_map[j])
			return (free_tab(new_map), ft_error("fail malloc copy ligne map\n"), NULL);
		while (map[j][i])
		{
			new_map[j][i] = map[j][i];
			i++;
		}
		new_map[j][i] = 0;
		j++;
	}
	new_map[j] = NULL;
	return (new_map);
}

char **get_map(char *file_name)
{
	t_list	*tmp_map;
	t_list	*new;
	char	**map;
	int fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (ft_error("fail open"), NULL);
	int a = 1;
	char *line;
	
	tmp_map = NULL;
	while (a)
	{
		line = get_next_line(fd);
           	if(!line)
				a = 0;
		new = lst_new(line);
		if (!new)
			return (NULL);
		add_back(&tmp_map, new);
	}
	map = convert_list(&tmp_map);
	return (map);
}

int	check_map_name(char *s, char *s2)
{
	int	len;
	int	len2;

	len = ft_strlen(s) - 1;
	len2 = ft_strlen(s2) - 1;
	while (len >= 0 && len2 >= 0)
	{
		if (s[len] != s2[len2])
			return (0);
		len--;
		len2--;
	}
	if (len2 == -1)
		return (1);
	else
		return (0);
}

int get_map_nb(char **map, char c)
{
	int	i;
	int	j;
	int	nb;
	
	nb = 0;
	i = 0;
	while(map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
				nb+=1;
			j++;
		}
		i++;
	}
	return (nb);
}

int	check_nb_elem(t_env *env)
{
	char **map;

	map = env->map.all_map;
	env->map.nb_collectible = get_map_nb(map, 'C');
	if (!env->map.nb_collectible)
		return (0);
	if (get_map_nb(map, 'P') != 1 || get_map_nb(map, 'E') != 1)
		return (0);
	return (1);
}

void	free_struct(t_env *env)
{
	(void) env;
	return ;
}

int	verif_wall(char **map)
{
	int	i;
	int	j;
	int	l;

	j = -1;
	l = ft_strlen(map[0]);
	while (map[++j])
	{
		i = 0;
		if ((j > 0 && map[j + 1]) && (map[j][0] != '1'\
		 || map[j][l - 2] != '1'))
			return (0);
		if ((map[j + 1]) && (map[j][0] != '1' && map[j][l - 2] != '1'))
			return (0);
		while (i < l - 2)
		{
			if (j == 0 && map[j][i] != '1')
				return (0);

			if (!map[j + 1] && (map[j][i] != '1'))
				return (0);
			i++;
		}
	}
	return (1);
}

int	mlx_close(t_env *env)
{
	(void) env;
		exit(0);
	return (0);
}

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

void	get_player_pos(char **map, int *x, int *y)
{
	int	i;
	int	j;
	int	player;

	player = 0;
	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == 'P')
			{
				player = 1;
				break ;
			}
			i++;
		}
		if (player)
			break ;
		j++;
	}
	*x = i;
	*y = j;
}

void	print_map(char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			write(1 , &map[j][i], 1);
			i++;
		}
		j++;
	}
}

void	*init_square(int color, int size)
{
	int	*ptr;
	int i;
	int	size_max;

	i = 0;
	size_max = size * size;
	ptr = malloc(sizeof(int) * size_max);
	if (!ptr)
		return (NULL);
	while (i < size_max)
	{
			ptr[i] = color;
			i++;
	}
	return (ptr);
}

void *init_circle(int color, int radius)
{
    int *ptr;
    int i = 0;
    int diameter = radius * 2;
    int x = 0, y = 0;
    ptr = malloc(sizeof(int) * diameter * diameter);
    if (!ptr)
        return NULL;

    while (y < diameter)
    {
        x = 0;
        while (x < diameter)
        {
            if (((x - radius) * (x - radius)) + ((y - radius)\
			 * (y - radius)) <= (radius * radius))
                ptr[i] = color;
            else
                ptr[i] = TRANSPARENT;
            i++;
            x++;
        }
        y++;
    }
    return (ptr);
}

void	img_cpy(t_img img, int *ptr, int size_line, int nb_line)
{
	int	i;
	int	j;

	ptr += (nb_line * IMG) * ((size_line * (IMG - 1)));
	i = 0;
	j = 0;
	while (i < img.size )
	{
		if (img.img[i] != (int)TRANSPARENT)
			ptr[j] = img.img[i];
		if (j == img.width-1)
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
	int player_y;

	player_x = env->map.p_x;
	player_y = env->map.p_y;
	if (player_x <= (env->mlx.win_x)/2)
	{
		index->x_start = 0;
		index->x_end = (env->mlx.win_x);
	}
	else if (env->map.size_line*IMG - player_x <= (env->mlx.win_x)/2)
	{
		index->x_end = env->map.size_line*IMG;
		index->x_start = index->x_end - (env->mlx.win_x);
	}
	else
	{
		index->x_start = player_x - (env->mlx.win_x)/2;
		index->x_end = index->x_start + (env->mlx.win_x / IMG);
	}
}

void	set_y_start(t_index *index, t_env *env)
{
	int	player_x;
	int player_y;

	player_x = env->map.p_x;
	player_y = env->map.p_y;
		if (player_y <= (env->mlx.win_y)/2)
	{
		index->y_start = 0;
		index->y_end = (env->mlx.win_y);
	}
	else if (env->map.height*IMG - player_y <= (env->mlx.win_y)/2)
	{
		index->y_end = env->map.height*IMG;
		index->y_start = index->y_end - (env->mlx.win_y);
	}
	else
	{
		index->y_start = player_y - ((env->mlx.win_y)/2);
		index->y_end = index->y_start + (env->mlx.win_y);
	}
}

void	get_start_map(t_index *index, t_env *env)
{
	set_x_start(index, env);
	set_y_start(index, env);
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

void	set_ptr(t_env *env, t_iter iter, int *c)
{
	if (iter.map[iter.j][iter.i] == '1')
		img_cpy(env->img.wall, &env->map.full_map[iter.count * IMG],\
		 env->map.size_line, iter.j);
	else if (iter.map[iter.j][iter.i] == 'E')
		img_cpy(env->img.exit, &env->map.full_map[iter.count * IMG],\
		 env->map.size_line, iter.j);
	else if (iter.map[iter.j][iter.i] == 'C')
	{
		img_cpy(env->img.objet, &env->map.full_map[(env->map.objets[*c].y * \
		(env->map.size_line * IMG)) + \
		env->map.objets[*c].x], env->map.size_line, 0);
		(*c)++;
	}
}

void	init_full_map(t_env *env)
{
	t_iter	iter;

	iter.count = 0;
	iter.j = 0;
	iter.c = 0;
	iter.map = env->map.all_map;
	set_map(env->map.full_map, env->map.size_line * IMG,\
	 IMG * env->map.size_line, IMG * env->map.height);
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
		if (j == (env.mlx.win_x)-1)
		{
			j = 0;
			all_map += (env.map.size_line * IMG);
		}
		else
			j++;
		i++;
	}
}

void	load_map(t_env *env)
{
		t_index	index;
		int		tmp_x;
		int		tmp_y;
		get_start_map(&index, env);
		tmp_x = env->map.p_x - (index.x_start);
		tmp_y = env->map.p_y - (index.y_start);
		copy_map(&env->map.full_map[index.y_start *\
		 (env->map.size_line * IMG) + index.x_start],\
		  env->map.win_map, *env);
		img_cpy(env->img.perso, &env->map.win_map[tmp_y*env->mlx.win_x+tmp_x],\
		 env->mlx.win_x / IMG, 0);
		mlx_put_image_to_window(env->mlx.mlx,\
		 env->mlx.mlx_win,env->img.mlx_img, 0, 0);
}

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
		nb/=10;
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

void remove_collectible(t_env *env, int i, int j)
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
		}
		c++;
	}
}

int	in_case_y(t_pos pos, int c_y, int size)
{
	if (c_y >= pos.new_y && c_y < pos.new_y + HEIGHT_PLAYER)
		return (1);
	if (c_y + size > pos.new_y && c_y + size <= pos.new_y + HEIGHT_PLAYER)
		return (1);
	if (c_y <= pos.new_y && c_y + size > pos.new_y + HEIGHT_PLAYER)
		return (1);
	return (0);
}

int	player_in_case(t_pos pos, t_case this_case, int pixel)
{
	int c_x;
	int c_y;
	int	size;

	c_x = this_case.x * IMG + pixel;
	c_y = this_case.y * IMG + pixel;
	size = IMG - (pixel * 2);

	if (c_x > pos.new_x && c_x < pos.new_x + WIDTH_PLAYER)
	{
		if (in_case_y(pos, c_y, size))
			return (1);
	}
	if (c_x + size > pos.new_x && c_x + size <= pos.new_x + WIDTH_PLAYER)
	{
		if (in_case_y(pos, c_y, size))
			return (1);
	}
	if (c_x <= pos.new_x && c_x + size > pos.new_x + WIDTH_PLAYER)
	{
		if (in_case_y(pos, c_y, size))
			return (1);
	}
	return (0);
}

int	verif_case(t_env *env, t_pos pos, char c, t_case this_case)
{
	int	pixel;

	pixel = 0;
	if (c == 'E')
		pixel = IMG / 2;
	if (c == 'C')
		pixel = IMG / 4;
	if (player_in_case(pos, this_case, pixel) \
		&& env->map.all_map[this_case.y][this_case.x] == c)
	{
		if (c == 'C')
		{
			remove_collectible(env, this_case.x, this_case.y);
			env->map.all_map[this_case.y][this_case.x] = '0';
		}
		return (1);
	}
	return (0);
}

void	init_zone(t_case zone[4], t_pos pos)
{
	zone[0].x = pos.new_x / IMG;
	zone[1].x = pos.new_x / IMG + 1;
	zone[2].x = pos.new_x / IMG;
	zone[3].x = pos.new_x / IMG + 1;
	zone[0].y = pos.new_y / IMG;
	zone[1].y = pos.new_y / IMG;
	zone[2].y = pos.new_y / IMG + 1;
	zone[3].y = pos.new_y / IMG + 1;
}

int check(t_env *env, t_pos pos, char c)
{
	t_case zone[4];

	init_zone(zone, pos);
	if (verif_case(env, pos, c, zone[0]))
		return (1);
	if (verif_case(env, pos, c, zone[1]))
		return (1);
	if (verif_case(env, pos, c, zone[2]))
		return (1);
	if (verif_case(env, pos, c, zone[3]))
		return (1);
	return (0);
}

void init_pos_l_r(t_pos *pos, t_env *env, int *move, int speed)
{
	pos->x = env->map.p_x;
	pos->y = env->map.p_y;
	pos->new_x = pos->x;
	pos->new_y = pos->y;
	if (env->key.right)
	{
		pos->new_x = pos->x + speed;
		*move += 1;
	}
	if (env->key.left)
	{
		pos->new_x = pos->x - speed;
		*move += 1;
	}
}
void init_pos_t_d(t_pos *pos, t_env *env, int *move, int speed)
{
	pos->x = env->map.p_x;
	pos->y = env->map.p_y;
	pos->new_x = pos->x;
	pos->new_y = pos->y;
	if (env->key.down)
	{
		pos->new_y = pos->y + speed;
		*move += 1;
	}
	if (env->key.up)
	{
		pos->new_y = pos->y - speed;
		*move += 1;
	}
}

int	multiple_key(t_env *env)
{
	int	ret;

	ret = 0;
	if ((env->key.left && env->key.down) || (env->key.left && env->key.up))
		ret += 1;
	if ((env->key.right && env->key.down) || (env->key.right && env->key.up))
		ret += 1;
	if ((env->key.up && env->key.left) || (env->key.up && env->key.right))
		ret += 1;
	if ((env->key.down && env->key.left) || (env->key.down && env->key.right))
		ret += 1;
	return (ret);
}

int	handle_key(t_env *env)
{
	t_pos	pos;
	int		move;
	int		speed;

	move = 0;
	speed = SPEED;
	if (multiple_key(env))
		speed = speed / 2;
	init_pos_t_d(&pos, env, &move, speed);
	if (!check(env, pos, '1'))
	{
		check(env, pos, 'C');
		env->map.p_y = pos.new_y;
		load_map(env);
	}
	init_pos_l_r(&pos, env, &move, speed);
	if (check(env, pos, '1'))
		return (0);
	check(env, pos, 'C');
	env->map.p_x = pos.new_x;
	load_map(env);
	if (move)
		print_nb_move(env);
	if (!env->map.nb_collectible && check(env, pos, 'E'))
		{
			ft_putstr("\nEnd!\n", 1);
			exit (0);
		}
	return (0);
}

void	get_map_size(t_env *env)
{
	env->map.height = tab_size(env->map.all_map);
	env->map.size_line = ft_strlen(env->map.all_map[0]) - 1;
	mlx_get_screen_size(env->mlx.mlx, &env->mlx.screen_x, &env->mlx.screen_y);
	env->mlx.screen_y -= 125;
	env->mlx.win_x = env->map.size_line * IMG;
	env->mlx.win_y = env->map.height * IMG;
	if (env->mlx.screen_x < env->mlx.win_x)
		env->mlx.win_x = env->mlx.screen_x;
	if (env->mlx.screen_y < env->mlx.win_y)
		env->mlx.win_y = env->mlx.screen_y;
}

void	ajust_touch(int *key1, int *key2)
{
		if (*key1 == 2)
			*key2 = 1;
		if (*key1 == 1)
			*key2 = 0;
		else if (*key2 == 2)
			*key2 = 1;
		*key1 = 0;
}

int	handle_keyrelease(int key_code, t_env *env)
{
	if (key_code == 65363 || key_code == 100)
		ajust_touch(&env->key.right, &env->key.left);
	else if (key_code == 65362 || key_code == 119)
		ajust_touch(&env->key.up, &env->key.down);
	else if (key_code == 65361 || key_code == 97)
		ajust_touch(&env->key.left, &env->key.right);
	else if (key_code == 65364 || key_code == 115)
		ajust_touch(&env->key.down, &env->key.up);
	return (key_code);
}

int	handle_keypress(int key_code,	t_env *env)
{
	if (key_code == 65307)
		exit(0);
	if (key_code == 65363 || key_code == 100)
	{
		if (env->key.left)
			env->key.right = 2;
		else
			env->key.right = 1;
		env->key.left = 0;
	}
	else if (key_code == 65362 || key_code == 119)
	{
		if (env->key.down)
			env->key.up = 2;
		else
			env->key.up = 1;
		env->key.down = 0;
	}
	else if (key_code == 65361 || key_code == 97)
	{
		if (env->key.right)
			env->key.left = 2;
		else
			env->key.left = 1;
		env->key.right = 0;
	}
	else if (key_code == 65364 || key_code == 115)
	{
		if (env->key.up)
			env->key.down = 2;
		else
			env->key.down = 1;
		env->key.up = 0;
	}
	return (key_code);
}

void	init_struct_img(t_img *img, int height, int width)
{
	img->size = height * width;
	img->height = height;
	img->width = width;
}

int	init_img(t_env *env)
{
	init_struct_img(&env->img.wall, IMG, IMG);
	init_struct_img(&env->img.objet, IMG / 2, IMG / 2);
	init_struct_img(&env->img.exit, IMG, IMG);
	init_struct_img(&env->img.perso, HEIGHT_PLAYER, WIDTH_PLAYER);
	env->img.wall.img = init_square(WALL , env->img.wall.size);
	env->img.exit.img = init_square(EXIT, env->img.exit.size);
	env->img.perso.img = init_square(PLAYER, env->img.perso.size);
	env->img.objet.img = init_circle(OBJET, env->img.objet.height / 2);
	if (!env->img.wall.img || !env->img.exit.img || !env->img.perso.img || !env->img.objet.img)
		return (free_struct(env), ft_error("fail malloc image\n"),0);
	return (1);
}

t_obj	*init_pos_obj(char **map, t_env env)
{
	int	size;
	int	i;
	int	j;
	int	c;
	t_obj	*objs;

	size = env.map.nb_collectible;
	j = 0;
	c = 0;
	objs = malloc(sizeof(t_obj) * size);
	while (map[j])
	{
		i = 0;
		while (map[j][i] && map[j][i] != '\n')
		{
			if (map[j][i] == 'C')
			{
				objs[c].x = (i * IMG) + ((IMG / 2) - (env.img.objet.width / 2));
				objs[c].y = (j * IMG) + ((IMG / 2) - (env.img.objet.height / 2));
				objs[c].i = i;
				objs[c].j = j;
				c++;
			}
			i++;
		}
		j++;
	}
	return (objs);
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
	mlx_hook(env->mlx.mlx_win, 3, 1<<1, handle_keyrelease, env);
	mlx_hook(env->mlx.mlx_win, 2, 1L<<0, handle_keypress, env);
	mlx_loop_hook(env->mlx.mlx, &handle_key, env);
}

int	verif_map(t_env *env)
{	
	(void) env;
	char **new_map;

	if (!verif_wall(env->map.all_map))
		return (0);
	new_map = cpy_map(env->map.all_map);
	if (!new_map)
		return (0);
	//flood_fill(env->map.p_x, env->map.p_y, new_map);
	//verif resuktat
	free_tab(new_map);
	return (1);
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
	get_player_pos(env->map.all_map, &env->map.p_x, &env->map.p_y);
	env->map.p_x = env->map.p_x * IMG + (IMG / 2 - WIDTH_PLAYER/2);
	env->map.p_y = env->map.p_y * IMG + (IMG / 2 - HEIGHT_PLAYER/2);
}

int	init_map(t_env *env)
{
	int	endian;
	int	size_line;
	int	bpp;

	env->map.full_map = malloc(sizeof(int) * env->map.height * IMG * env->map.size_line * IMG);
	if (!env->map.full_map)
		return (0);
	env->img.mlx_img = (int *)mlx_new_image(env->mlx.mlx, env->mlx.win_x, env->mlx.win_y);
	if (!env->img.mlx_img)
		return (0);
	env->map.win_map = (int *)mlx_get_data_addr(env->img.mlx_img, &bpp, &size_line, &endian);
	if (!init_img(env))
		return (0);
	env->map.objets = init_pos_obj(env->map.all_map, *env);
	if (!env->map.objets)
		return (0);
	return (1);
}

int	map(t_env *env, char *arg)
{
	env->map.all_map = get_map(arg);
	if (!env->map.all_map)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_env env;

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
	set_hooks_mlx(&env);
	mlx_loop(env.mlx.mlx);
}
