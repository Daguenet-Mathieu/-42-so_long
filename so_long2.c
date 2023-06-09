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
		return (ft_error("probleme avec malloc\n"), NULL);
	while (map[j])
	{
		i = 0;
		new_map[j] = malloc(ft_strlen(map[j] + 1));
		if (new_map[j])
			return (free_tab(new_map), ft_error("probleme avec malloc\n"), NULL);
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
	env->map.nb_collectible = get_map_nb(env->map.all_map, 'C');
	if (get_map_nb(env->map.all_map, 'P') != 1 || get_map_nb(env->map.all_map, 'E') != 1)
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
	int	len;

	j = 0;
	len = ft_strlen(map[0]);
	while (map[j])
	{
		i = 0;
		if ((j > 0 && map[j + 1]) && (map[j][0] != '1' || map[j][len - 2] != '1'))
			return (0);
		if ((map[j + 1]) && (map[j][0] != '1' && map[j][len - 2] != '1'))
			return (0);
		while (i < len - 2)
		{
			if (j == 0 && map[j][i] != '1')
				return (0);

			if (!map[j + 1] && (map[j][i] != '1'))
				return (0);
			i++;
		}
		j++;
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
	//printf("radius == %d\n", radius);
    ptr = malloc(sizeof(int) * diameter * diameter);
    if (!ptr)
        return NULL;

    while (y < diameter)
    {
        x = 0;
        while (x < diameter)
        {
            if (((x - radius) * (x - radius)) + ((y - radius) * (y - radius)) <= (radius * radius))
                ptr[i] = color;
            else
                ptr[i] = TRANSPARENT;
			//printf("i == %d et color == %x\n",i, ptr[i]);
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

	ptr += (nb_line * WIDTH_IMG) * ((size_line * (WIDTH_IMG - 1)));
	//printf("ptr == %p\n", ptr);
	i = 0;
	j = 0;
	//printf("size == %d et i == %d\n",img.size, i);
	while (i < img.size )
	{
		if (img.img[i] != (int)TRANSPARENT)
			ptr[j] = img.img[i];
		if (j == img.width-1)
		{
			j = 0;
			ptr += (size_line) * WIDTH_IMG;
		}
		else
			j++;
		i++;
	}
}

void	get_start_map(t_index *index, t_env *env)
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
	else if (env->map.size_line*WIDTH_IMG - player_x <= (env->mlx.win_x)/2)
	{
		index->x_end = env->map.size_line*WIDTH_IMG;
		index->x_start = index->x_end - (env->mlx.win_x);
	}
	else
	{
		index->x_start = player_x - (env->mlx.win_x)/2;
		index->x_end = index->x_start + (env->mlx.win_x / WIDTH_IMG);
	}
	if (player_y <= (env->mlx.win_y)/2)
	{
		index->y_start = 0;
		index->y_end = (env->mlx.win_y);
	}
	else if (env->map.height*HEIGHT_IMG - player_y <= (env->mlx.win_y)/2)
	{
		index->y_end = env->map.height*HEIGHT_IMG;
		index->y_start = index->y_end - (env->mlx.win_y);
	}
	else
	{
		index->y_start = player_y - ((env->mlx.win_y)/2);
		index->y_end = index->y_start + (env->mlx.win_y);
	}
}

void	set_map(int *ptr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ptr[i] = FLOOR;
		i++;
	}
}

void	init_full_map(t_env *env)
{
	int		i;
	int		j;
	int		count;
	char	**map;
	int		c;

	count = 0;
	j = 0;
	c = 0;
	map = env->map.all_map;
	set_map(env->map.full_map, env->map.size_line*WIDTH_IMG*env->map.height*HEIGHT_IMG);
	while (map[j])
	{
		i = 0;
		while (map[j][i] && map[j][i] != '\n')
		{
			if (map[j][i] == '1')
				img_cpy(env->img.wall, &env->map.full_map[count*WIDTH_IMG], env->map.size_line, j);
			else if (map[j][i] == 'E')
				img_cpy(env->img.exit, &env->map.full_map[count*WIDTH_IMG], env->map.size_line, j);
			else if (map[j][i] == 'C')
			{
			//	printf("start == %p et ptr == %p , winx == %d et win y = %d, c == %d pos y == %d && pos x == %d et decallage == %d ou %X\n",env->map.full_map, &env->map.win_map[env->map.objets[c].y_start*env->mlx.win_x+env->map.objets[c].x_start], env->mlx.win_x, env->mlx.win_x, c, env->map.objets[c].y_start, env->map.objets[c].x_start, (env->map.objets[c].y_start*env->mlx.win_x)+env->map.objets[c].x_start, (env->map.objets[c].y_start*env->mlx.win_x)+env->map.objets[c].x_start);
				img_cpy(env->img.objet, &env->map.full_map[(env->map.objets[c].y_start*(env->map.size_line*WIDTH_IMG))+env->map.objets[c].x_start], env->map.size_line, 0);
				c++;
			//	img_cpy(env->img.objet, &env->map.full_map[count*WIDTH_IMG], env->map.size_line, j);
			}
			count++;
			i++;
		}
		j++;
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
			all_map += (env.map.size_line * WIDTH_IMG);
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
	//	int		i;

		//i = 0;
		get_start_map(&index, env);
		tmp_x = env->map.p_x - (index.x_start);
		tmp_y = env->map.p_y - (index.y_start);
		printf("plyer x == %d, player y == %d, tmpx == %d, tmpy == %d\n",env->map.p_x, env->map.p_y, tmp_x, tmp_y);
		copy_map(&env->map.full_map[index.y_start*(env->map.size_line*WIDTH_IMG)+index.x_start], env->map.win_map, *env);
		img_cpy(env->img.perso, &env->map.win_map[tmp_y*env->mlx.win_x+tmp_x], env->mlx.win_x / WIDTH_IMG, 0);
		//while (i < env->map.nb_collectible)
		//{
		//	if (env->map.objets[i].y_start > index.y_start && env->map.objets[i].y_start > index.y_start && env->map.objets[i].y_start > index.y_start && env->map.objets[i].y_end > index.x_end)
		//		img_cpy(env->img.objet, &env->map.win_map[env->map.objets[i].y_start*env->mlx.win_x+env->map.objets[i].x_start], env->mlx.win_x / WIDTH_IMG, 0);
		//	i++;
		//}
		mlx_put_image_to_window(env->mlx.mlx, env->mlx.mlx_win,env->img.mlx_img, 0, 0);
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

int	check_collision2(int player ,int case_check)
{
	int	collision;

	collision = 0;
		if ((player > case_check && player <= case_check-1 + HEIGHT_IMG) /*|| (player < case_check && player >= case_check)*/)
			collision = 1;

	if (collision)
		return (1);
	return (0);
}

int	check_collision(t_env *env, t_pos pos, char c)
{
	//printf("p-si == %d\n", WIDTH_IMG - WIDTH_PLAYER );
	if (((pos.new_x) % HEIGHT_IMG) >= WIDTH_IMG - WIDTH_PLAYER && env->map.all_map[(pos.new_y)/HEIGHT_IMG][pos.new_x/WIDTH_IMG] == c)
		return (0);
	if (((pos.new_y) % HEIGHT_IMG) > HEIGHT_IMG - HEIGHT_PLAYER && env->map.all_map[(pos.new_y)/HEIGHT_IMG][pos.new_x/WIDTH_IMG] == c)
		return (0);
	if ((pos.new_x % WIDTH_IMG) > WIDTH_IMG - WIDTH_PLAYER && env->map.all_map[pos.new_y/HEIGHT_IMG][pos.new_x/WIDTH_IMG+1] == c)
		return (0);
	if ((pos.new_y % HEIGHT_IMG) > (WIDTH_IMG - HEIGHT_PLAYER) && env->map.all_map[pos.new_y/HEIGHT_IMG + 1][pos.new_x/WIDTH_IMG] == c)
		return (0);
	if ((pos.new_x % WIDTH_IMG) > WIDTH_IMG - WIDTH_PLAYER && (pos.new_y % HEIGHT_IMG) > WIDTH_IMG - HEIGHT_PLAYER \
		&& env->map.all_map[pos.new_y/HEIGHT_IMG + 1][pos.new_x/WIDTH_IMG + 1] == c)
		return (0);
	return (1);
}

int	check_wall(t_env *env, t_pos pos)
{
	if (!check_collision(env, pos, '1'))
		return (0);
	return (1);
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
	
	c = 0;
	//printf("i == %d et j == %d\n", i, j);
	while (c < env->map.nb_collectible)
	{
		//printf("les objets sont i == %d et j == %d\n", env->map.objets[c].i, env->map.objets[c].j);
		if (env->map.objets[c].j == j && env->map.objets[c].i == i)
			delete_obj(&env->map.objets[c], env->map.nb_collectible - c);
		c++;
	}
}

int	player_in_case(t_pos pos, int case_x, int case_y, int pixel)
{
	//(void) nb_pixel;
	int cx = case_x;
	int cy = case_y;
	int px = pos.new_x;
	int py = pos.new_y;
	//pos.new_x+= WIDTH_PLAYER/2;
	//pos.new_y+= HEIGHT_PLAYER/2;
	printf("\n\n\ni == %d, j == %d \n", case_x, case_y);
	printf("player x == %d et player y == %d\n", pos.new_x, pos.new_y);
	if (px + WIDTH_PLAYER > cx + pixel && px + WIDTH_PLAYER < cx + WIDTH_IMG - pixel)
	{
		if (py + HEIGHT_PLAYER > cy + pixel && py + HEIGHT_PLAYER < cy + HEIGHT_IMG - pixel)
			return (printf("dans la case i == %d, j == %d\n", case_x/WIDTH_IMG , case_y/HEIGHT_IMG), 1);
		if (py >= cy + pixel && py < cy + HEIGHT_IMG - pixel)
			return (printf("dans la case i == %d, j == %d\n", case_x/WIDTH_IMG , case_y/HEIGHT_IMG), 1);
	}
	if (px >= cx + pixel && px < cx + WIDTH_IMG - pixel)
	{
		if (py + HEIGHT_PLAYER > cy + pixel && py + HEIGHT_PLAYER < cy + HEIGHT_IMG - pixel)
			return (printf("dans la case i == %d, j == %d\n", case_x/WIDTH_IMG , case_y/HEIGHT_IMG), 1);
		if (py >= cy + pixel && py < cy + HEIGHT_IMG - pixel)
			return (printf("dans la case i == %d, j == %d\n", case_x/WIDTH_IMG , case_y/HEIGHT_IMG), 1);
	}
	if (px+WIDTH_PLAYER/2 >= cx + pixel && px+WIDTH_PLAYER/2 < cx + WIDTH_IMG)
	{
		if (py+HEIGHT_PLAYER/2 >= cy + pixel && py+HEIGHT_PLAYER/2 < cy + HEIGHT_IMG - pixel)
			return (printf("dans la case i == %d, j == %d\n", case_x/WIDTH_IMG , case_y/HEIGHT_IMG), 1);
	}
	if (px+WIDTH_PLAYER/2 <= cx + WIDTH_IMG - pixel && px+WIDTH_PLAYER/2 > cx)
	{
		if (py+HEIGHT_PLAYER/2 <= cy + HEIGHT_IMG - pixel && py+HEIGHT_PLAYER/2 > cy)
			return (printf("dans la case i == %d, j == %d\n", case_x/WIDTH_IMG , case_y/HEIGHT_IMG), 1);
	}
	return (printf("pas dans la case i == %d, j == %d\n", case_x/WIDTH_IMG , case_y/HEIGHT_IMG), 0);
	//trouver l'objet correspondant a la case et verifier si le start du joueur est superueur de int pixel passe en parametres
	// et si il est inferieur d'au ;oins x pixel ou la meme chose avec end du joueur pour x et y
}


int check_exit(t_env *env, t_pos pos, char c, int pixel)
{
	int check;

	check = 0;

	if (player_in_case(pos, (pos.new_x/WIDTH_IMG)*WIDTH_IMG, (pos.new_y)/HEIGHT_IMG*HEIGHT_IMG, pixel) && env->map.all_map[(pos.new_y)/HEIGHT_IMG][pos.new_x/WIDTH_IMG] == c)
		check = 1;//appeler fonctio aui prend &check en param et fais les verif obj si c == E?
	if ( player_in_case(pos, (pos.new_x/WIDTH_IMG+1)*WIDTH_IMG, (pos.new_y)/HEIGHT_IMG*HEIGHT_IMG, pixel) && env->map.all_map[(pos.new_y)/HEIGHT_IMG][pos.new_x/WIDTH_IMG + 1] == c)
		check = 1;
	if (player_in_case(pos, (pos.new_x/WIDTH_IMG)*WIDTH_IMG, (pos.new_y/HEIGHT_IMG + 1)*HEIGHT_IMG, pixel) && env->map.all_map[pos.new_y/HEIGHT_IMG + 1][pos.new_x/WIDTH_IMG] == c)
		check = 1;
	if (player_in_case(pos, (pos.new_x/WIDTH_IMG-1)*WIDTH_IMG , (pos.new_y)/HEIGHT_IMG*HEIGHT_IMG, pixel) && env->map.all_map[pos.new_y/HEIGHT_IMG][pos.new_x/WIDTH_IMG - 1] == c)
		check = 1;
	if (player_in_case(pos, (pos.new_x)/WIDTH_IMG*WIDTH_IMG, (pos.new_y/HEIGHT_IMG-1)*HEIGHT_IMG, pixel) && env->map.all_map[pos.new_y/HEIGHT_IMG - 1][pos.new_x/WIDTH_IMG] == c)
		check = 1;
	if (player_in_case(pos, (pos.new_x/WIDTH_IMG+1)*WIDTH_IMG, (pos.new_y/HEIGHT_IMG+1)*HEIGHT_IMG, pixel) && env->map.all_map[pos.new_y/HEIGHT_IMG + 1][pos.new_x/WIDTH_IMG + 1] == c)
		check = 1;
	if (player_in_case(pos, (pos.new_x/WIDTH_IMG-1)*WIDTH_IMG, (pos.new_y/HEIGHT_IMG-1)*HEIGHT_IMG, pixel) && env->map.all_map[pos.new_y/HEIGHT_IMG - 1][pos.new_x/WIDTH_IMG - 1] == c)
		check = 1;
	if (player_in_case(pos, (pos.new_x/WIDTH_IMG-1)*WIDTH_IMG, (pos.new_y/HEIGHT_IMG+1)*HEIGHT_IMG, pixel) && env->map.all_map[pos.new_y/HEIGHT_IMG + 1][pos.new_x/WIDTH_IMG - 1] == c)
		check = 1;
	if (player_in_case(pos, (pos.new_x/WIDTH_IMG+1)*WIDTH_IMG, (pos.new_y/HEIGHT_IMG-1)*HEIGHT_IMG, pixel) && env->map.all_map[pos.new_y/HEIGHT_IMG - 1][pos.new_x/WIDTH_IMG + 1] == c)
		check = 1;
//	print_map(env->map.all_map);
	return (check);
}

int check_collectible(t_env *env, t_pos pos, char c, int pixel)
{
	int check;

	check = 0;

	if (player_in_case(pos, (pos.new_x/WIDTH_IMG)*WIDTH_IMG, (pos.new_y)/HEIGHT_IMG*HEIGHT_IMG, pixel) && env->map.all_map[(pos.new_y)/HEIGHT_IMG][pos.new_x/WIDTH_IMG] == c)
	{
		remove_collectible(env, pos.new_x/WIDTH_IMG, (pos.new_y)/HEIGHT_IMG);//transmettre i et j correxpondant a la case
		env->map.all_map[(pos.new_y)/HEIGHT_IMG][pos.new_x/WIDTH_IMG] = '0';
		env->map.nb_collectible -= 1;
		check = 1;
	}
	if ( player_in_case(pos, (pos.new_x/WIDTH_IMG+1)*WIDTH_IMG, (pos.new_y)/HEIGHT_IMG*HEIGHT_IMG, pixel) && env->map.all_map[(pos.new_y)/HEIGHT_IMG][pos.new_x/WIDTH_IMG + 1] == c)
	{
		remove_collectible(env, pos.new_x/WIDTH_IMG + 1, (pos.new_y)/HEIGHT_IMG);
		env->map.all_map[(pos.new_y)/HEIGHT_IMG][pos.new_x/WIDTH_IMG + 1] = '0';
		env->map.nb_collectible -= 1;
		check = 1;
	}
	if (player_in_case(pos, (pos.new_x/WIDTH_IMG)*WIDTH_IMG, (pos.new_y/HEIGHT_IMG + 1)*HEIGHT_IMG, pixel) && env->map.all_map[pos.new_y/HEIGHT_IMG + 1][pos.new_x/WIDTH_IMG] == c)
	{
		remove_collectible(env, pos.new_x/WIDTH_IMG, pos.new_y/HEIGHT_IMG + 1);
		env->map.all_map[pos.new_y/HEIGHT_IMG + 1][pos.new_x/WIDTH_IMG] = '0';
		env->map.nb_collectible -= 1;
		check = 1;
	}
	if (player_in_case(pos, (pos.new_x/WIDTH_IMG-1)*WIDTH_IMG , (pos.new_y)/HEIGHT_IMG*HEIGHT_IMG, pixel) && env->map.all_map[pos.new_y/HEIGHT_IMG][pos.new_x/WIDTH_IMG - 1] == c)
	{
		remove_collectible(env, pos.new_x/WIDTH_IMG - 1, pos.new_y/HEIGHT_IMG);
		env->map.all_map[pos.new_y/HEIGHT_IMG][pos.new_x/WIDTH_IMG - 1] = '0';
		env->map.nb_collectible -= 1;
		check = 1;
	}
	if (player_in_case(pos, (pos.new_x)/WIDTH_IMG*WIDTH_IMG, (pos.new_y/HEIGHT_IMG-1)*HEIGHT_IMG, pixel) && env->map.all_map[pos.new_y/HEIGHT_IMG - 1][pos.new_x/WIDTH_IMG] == c)
	{
		remove_collectible(env, pos.new_x/WIDTH_IMG, pos.new_y/WIDTH_IMG - 1);
		env->map.all_map[pos.new_y/HEIGHT_IMG - 1][pos.new_x/WIDTH_IMG] = '0';
		env->map.nb_collectible -= 1;
		check = 1;
	}
		if (player_in_case(pos, (pos.new_x/WIDTH_IMG+1)*WIDTH_IMG, (pos.new_y/HEIGHT_IMG+1)*HEIGHT_IMG, pixel) && env->map.all_map[pos.new_y/HEIGHT_IMG + 1][pos.new_x/WIDTH_IMG + 1] == c)
	{
		remove_collectible(env, pos.new_x/WIDTH_IMG + 1, pos.new_y/WIDTH_IMG + 1);
		env->map.all_map[pos.new_y/HEIGHT_IMG + 1][pos.new_x/WIDTH_IMG +1] = '0';
		env->map.nb_collectible -= 1;
		check = 1;
	}
		if (player_in_case(pos, (pos.new_x/WIDTH_IMG-1)*WIDTH_IMG, (pos.new_y/HEIGHT_IMG-1)*HEIGHT_IMG, pixel) && env->map.all_map[pos.new_y/HEIGHT_IMG - 1][pos.new_x/WIDTH_IMG - 1] == c)
	{
		remove_collectible(env, pos.new_x/WIDTH_IMG - 1, pos.new_y/WIDTH_IMG - 1);
		env->map.all_map[pos.new_y/HEIGHT_IMG - 1][pos.new_x/WIDTH_IMG - 1] = '0';
		env->map.nb_collectible -= 1;
		check = 1;
	}	if (player_in_case(pos, (pos.new_x/WIDTH_IMG-1)*WIDTH_IMG, (pos.new_y/HEIGHT_IMG+1)*HEIGHT_IMG, pixel) && env->map.all_map[pos.new_y/HEIGHT_IMG + 1][pos.new_x/WIDTH_IMG - 1] == c)
	{
		remove_collectible(env, pos.new_x/WIDTH_IMG - 1, pos.new_y/WIDTH_IMG + 1);
		env->map.all_map[pos.new_y/HEIGHT_IMG + 1][pos.new_x/WIDTH_IMG - 1] = '0';
		env->map.nb_collectible -= 1;
		check = 1;
	}	if (player_in_case(pos, (pos.new_x/WIDTH_IMG+1)*WIDTH_IMG, (pos.new_y/HEIGHT_IMG-1)*HEIGHT_IMG, pixel) && env->map.all_map[pos.new_y/HEIGHT_IMG - 1][pos.new_x/WIDTH_IMG + 1] == c)
	{
		remove_collectible(env, pos.new_x/WIDTH_IMG + 1, pos.new_y/WIDTH_IMG - 1);
		env->map.all_map[pos.new_y/HEIGHT_IMG - 1][pos.new_x/WIDTH_IMG + 1] = '0';
		env->map.nb_collectible -= 1;
		check = 1;
	}
	//print_map(env->map.all_map);
	return (check);
}

int	handle_key(t_env *env)
{
	t_pos	pos;

	if (!env->key.up && !env->key.down && !env->key.left && !env->key.right)
		return (0);
	if ((env->key.up && env->key.down) || (env->key.left && env->key.right))
		return (0);
	//printf("dans handle key == r == %d, l == %d, up == %d, d == %d\n" , env->key.right, env->key.left, env->key.up,env->key.down);
	pos.x = env->map.p_x;
	pos.y = env->map.p_y;
	pos.new_x = pos.x;
	pos.new_y = pos.y;
	if (env->key.up)
		pos.new_y = pos.y - SPEED;
	if (env->key.right)
		pos.new_x = pos.x + SPEED;
	if (env->key.left)
		pos.new_x = pos.x - SPEED;
	if (env->key.down)
		pos.new_y = pos.y + SPEED;
//	if (map[pos.new_y][pos.new_x] == '1')
//		return (0);
//	if (map[pos.y][pos.x] == 'P')
//		map[pos.y][pos.x] = '0';
//	else if (map[pos.y][pos.x] == 'p')
//		map[pos.y][pos.x] = 'E';
//	if (map[pos.new_y][pos.new_x] == 'C')
//		env->map.nb_collectible -= 1;
//	if (map[pos.new_y][pos.new_x] == 'E')
//		map[pos.new_y][pos.new_x] = 'p';
//	else
//		map[pos.new_y][pos.new_x] = 'P';

//collision == (WIDTH_IMG - HEIGHT_PLAYER) + (35*WIDTH_IMG/100)
	//printf("modulo x == %d et modulo y == %d \n", (pos.new_x) % HEIGHT_IMG, (pos.new_y) % HEIGHT_IMG);
	if (!check_wall(env, pos))
		return (0);
	if (check_collectible(env, pos, 'C', WIDTH_IMG/4))
		init_full_map(env);
	//if ((pos.new_y % HEIGHT_IMG) > WIDTH_IMG - HEIGHT_PLAYER && map[pos.new_y/HEIGHT_IMG][pos.new_x/WIDTH_IMG + 1] == '1')
	//	return (0);
	//if (map[pos.new_y/HEIGHT_IMG][pos.new_x/WIDTH_IMG+1] == '1' && (pos.new_y % HEIGHT_IMG) > 0)
	//	return (0);
	//printf("coucou le deplcement\n");
	//if ((pos.new_y + HEIGHT_PLAYER) % HEIGHT_IMG == 1 && map[(pos.new_y/HEIGHT_IMG) + 1][pos.new_x/WIDTH_IMG] == '1')
	//	return (0);
	//if (map[(pos.new_y/HEIGHT_PLAYER)+ 1][pos.new_x/WIDTH_IMG] == '1' && (pos.new_y + HEIGHT_PLAYER) < (pos.new_y/HEIGHT_IMG + 1))
	//	return (0);
	//if (check_collision(map, pos.new_x, pos.new_y))
	//	return (0);
	env->map.p_x = pos.new_x;
	env->map.p_y = pos.new_y;
	load_map(env);
	print_nb_move(env);
	//print_map(map);
	if (!env->map.nb_collectible && check_exit(env, pos, 'E', WIDTH_IMG/2 - 20))
		{
			ft_putstr("\nvictoire!\n", 1);
			exit (0);
		}
	//  env->key.up = 0;
	//  env->key.down = 0;
	//  env->key.right = 0;
	//  env->key.left = 0;
	return (0);
}

void	get_map_size(t_env *env)
{
	mlx_get_screen_size(env->mlx.mlx, &env->mlx.screen_x, &env->mlx.screen_y);
	env->mlx.screen_y -= 130;
	env->mlx.win_x = env->map.size_line;
	env->mlx.win_y = env->map.height;
	env->mlx.screen_x = env->mlx.screen_x / WIDTH_IMG;
	env->mlx.screen_y = env->mlx.screen_y / WIDTH_IMG;
	//env->mlx.win_x = (env->mlx.win_x) * WIDTH_IMG;
	//env->mlx.win_y = (env->mlx.win_y) * WIDTH_IMG;
	if (env->mlx.screen_x < env->mlx.win_x)
		env->mlx.win_x = env->mlx.screen_x;
	if (env->mlx.screen_y < env->mlx.win_y)
		env->mlx.win_y = env->mlx.screen_y;
	env->mlx.win_x *= WIDTH_IMG;
	env->mlx.win_y *= WIDTH_IMG;
}

int	handle_keyrelease(int key_code, 	t_env *env)
{
	//printf("loop = %d\n", env->key.loop_count);
	env->key.loop_count = 0;
	if (key_code == 65363 || key_code == 100)
		env->key.right = 0;
	else if (key_code == 65362 || key_code == 119)
		env->key.up = 0;
	else if (key_code == 65361 || key_code == 97)
		env->key.left = 0;
	else if (key_code == 65364 || key_code == 115)
		env->key.down = 0;
	//printf("dans key release key code = %d== r == %d, l == %d, up == %d, d == %d\n" , key_code , env->key.right, env->key.left, env->key.up,env->key.down);
	return (key_code);
}

int	handle_keypress(int key_code,	t_env *env)
{
	env->key.loop_count += 1;
	if (key_code == 65307)
		exit(0);
	if (key_code == 65363 || key_code == 100)
		env->key.right = 1;
	else if (key_code == 65362 || key_code == 119)
		env->key.up = 1;
	else if (key_code == 65361 || key_code == 97)
		env->key.left = 1;
	else if (key_code == 65364 || key_code == 115)
		env->key.down = 1;
	//handle_key(env);
	//printf("dans keypress keycode = %d == r == %d, l == %d, up == %d, d == %d\n" ,key_code, env->key.right, env->key.left, env->key.up,env->key.down);
	return (key_code);
}

void	init_struct_img(t_img *img, int height, int width)
{
	img->size = height * width;
	img->height = height;
	img->width = width;
	//printf("img h == %d et img w == %d\n", img->height, img->width);
}

int	init_img(t_env *env)
{
	init_struct_img(&env->img.wall, HEIGHT_IMG, WIDTH_IMG);
	init_struct_img(&env->img.objet, HEIGHT_IMG / 2, WIDTH_IMG / 2);
	init_struct_img(&env->img.exit, HEIGHT_IMG, WIDTH_IMG);
	init_struct_img(&env->img.perso, HEIGHT_PLAYER, WIDTH_PLAYER);
	env->img.wall.img = init_square(WALL , env->img.wall.size);
	env->img.exit.img = init_square(EXIT, env->img.exit.size);
	env->img.perso.img = init_square(PLAYER, env->img.perso.size);
	env->img.objet.img = init_circle(OBJET, env->img.objet.height / 2);
	if (!env->img.wall.img || !env->img.exit.img || !env->img.perso.img || !env->img.objet.img)
		return (free_struct(env), ft_error("coucou le malloc d'image rate\n"),0);
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
				objs[c].x_start = (i * WIDTH_IMG) + ((WIDTH_IMG / 2) - (env.img.objet.width / 2));
				objs[c].y_start = (j * HEIGHT_IMG) + ((HEIGHT_IMG / 2) - (env.img.objet.height / 2));
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

int	main(int ac, char **av)
{
	t_env env;
	int	bpp;
	int	endian;
	int	size_line;

	if (ac != 2)
		return (1);
	init_struct(&env);
	env.mlx.mlx = mlx_init();
	if (!env.mlx.mlx)
		return (1);
	if (!check_map_name(av[1], ".ber"))
		return (1);
	env.map.all_map = get_map(av[1]);
	if (!env.map.all_map)
		return (1);
	env.map.height = tab_size(env.map.all_map);
	env.map.size_line = ft_strlen(env.map.all_map[0]) - 1;
	env.map.full_map = malloc(sizeof(int) * env.map.height * HEIGHT_IMG * env.map.size_line * WIDTH_IMG);
	if (!env.map.full_map)
		return (1);
	env.map.nb_move = 0;
	env.map.nb_collectible = get_map_nb(env.map.all_map, 'C');
	get_player_pos(env.map.all_map, &env.map.p_x, &env.map.p_y);
	printf("player x == %d, player y == %d\n", env.map.p_x, env.map.p_y);
	//flood_fill(env.map.p_x, env.map.p_y, env.map.all_map);
	//print_map(env.map.all_map);
	//return (0);
	env.map.p_x = env.map.p_x * WIDTH_IMG + (WIDTH_IMG / 2 - WIDTH_PLAYER/2);
	env.map.p_y = env.map.p_y * HEIGHT_IMG + (HEIGHT_IMG / 2 - HEIGHT_PLAYER/2);
	if (!verif_wall(env.map.all_map))
		return (1);
	get_map_size(&env);
	env.img.mlx_img = (int *)mlx_new_image(env.mlx.mlx, env.mlx.win_x, env.mlx.win_y);
	if (!env.img.mlx_img)
		return 1;
	env.map.win_map = (int *)mlx_get_data_addr(env.img.mlx_img, &bpp, &size_line, &endian);
	if (!init_img(&env))
		return (free_struct(&env), 1);
	env.map.objets = init_pos_obj(env.map.all_map, env);
	if (!env.map.objets)
		return (free_struct(&env), 0);
	env.mlx.mlx_win = mlx_new_window(env.mlx.mlx, env.mlx.win_x, env.mlx.win_y, "so_long");
	init_full_map(&env);
	load_map(&env);
	if (!env.mlx.mlx_win)
		return (free_struct(&env), 1);
	mlx_hook(env.mlx.mlx_win, 17, 0, mlx_close, &env);
	mlx_hook(env.mlx.mlx_win, 3, 1<<1, handle_keyrelease, &env);
	mlx_hook(env.mlx.mlx_win, 2, 1L<<0, handle_keypress, &env);
	mlx_loop_hook(env.mlx.mlx, &handle_key, &env);
	mlx_loop(env.mlx.mlx);
}
