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
#include "mlx_linux/mlx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

# ifndef SIZE_LINE
#  define SIZE_LINE 1 
# endif

# ifndef VERTICAL
#  define VERTICAL 2
# endif

# ifndef HORIZON 
#  define HORIZON 1
# endif

# ifndef MINI_MAP
#  define MINI_MAP 128
# endif

# ifndef MINI_PX
#  define MINI_PX 1
# endif

# ifndef WIDTH_IMG
#  define WIDTH_IMG 32
# endif

# ifndef HEIGHT_IMG
#  define HEIGHT_IMG 32
# endif

# ifndef HEIGHT_PLAYER
#  define HEIGHT_PLAYER 16
# endif

# ifndef WIDTH_PLAYER
#  define WIDTH_PLAYER 16
# endif

# ifndef SPEED
#  define SPEED 1 /*WIDTH_IMG/12*/
# endif

# ifndef PLAYER
#  define PLAYER 0x0000FF
# endif

# ifndef FLOOR
#  define FLOOR 0x136d15
# endif

# ifndef FLOOR2
#  define FLOOR2 0x006400
# endif

# ifndef EXIT
#  define EXIT 0xFF00FF
# endif

# ifndef OBJET
#  define OBJET 0xaa8c2c
# endif

# ifndef WALL
#  define WALL 0x808080
# endif

typedef struct	s_index
{
	int	x_start;
	int	x_end;
	int	y_start;
	int	y_end;
}				t_index;

typedef struct	s_minimap
{
	void	*wall;
	void	*perso;
	void	*collectible;
	void	*exit;
	int		img_size;
	int		size_unit;
	int		nb_element_x;
	int		nb_element_y;
	int		player_x;
	int		player_y;

	//utiliser s_index;
}				t_minimap;

typedef struct s_key
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	loop_count;
}				t_key;

typedef struct	s_pos
{
		int		y;
		int		x;
		int		new_y;
		int		new_x;
}				t_pos;

typedef struct	s_mlx
{
		void	*mlx;
		void	*mlx_win;
		int		win_x;
		int		win_y;
		int		screen_x;
		int		screen_y;
}				t_mlx;

typedef struct	s_map
{
		char	**all_map;
		int		*win_map;
		int		*full_map;
		int		nb_collectible;
		int		nb_move;
		int		p_x;
		int		p_y;
		int		height;
		int		size_line;
}				t_map;

typedef struct	s_img
{
		void	*floor;
		void	*wall;
		void	*objet;
		void	*exit;
		void	*perso;
		void	*mlx_img;
}				t_img;

typedef struct	s_env
{
		t_img	img;
		t_mlx	mlx;
		t_map	map;	
		t_key	key;
		t_pos	pos;
		t_index	index;
		int		loop;
}				t_env;


typedef struct s_list
{
	char	*content;
	struct s_list *next;
}		t_list;


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

int	mlx_close(t_env env)
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
			else
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

	i = 0;
	ptr = malloc(sizeof(int) * size*size);
	if (!ptr)
		return (NULL);
	while (i < size*size)
	{
			ptr[i] = color;
			i++;
	}
	return (ptr);
}

// void	*init_circle(int color)
// {
// 	int	*ptr;
// 	int i;
// 	int	radius;

// 	i = 0;
// 	radius = WIDTH_IMG/3;
// 	ptr = malloc(sizeof(int) * WIDTH_IMG*WIDTH_IMG);
// 	if (!ptr)
// 		return (NULL);
// 	while (i < WIDTH_IMG*WIDTH_IMG)
// 	{
// 		ptr[i] = color;
// 		i++;
// 	}
// 	return (ptr);
// }

void	*init_circle(int color)
{
	int	*ptr;
	int i;
	int	radius;
	int x, y;

	i = 0;
	radius = WIDTH_IMG/4;
	ptr = malloc(sizeof(int) * WIDTH_IMG*HEIGHT_IMG);
	if (!ptr)
		return (NULL);

	for (y = 0; y < WIDTH_IMG; y++)
	{
		for (x = 0; x < WIDTH_IMG; x++)
		{
			int dx = x - WIDTH_IMG / 2;
			int dy = y - WIDTH_IMG / 2;
			int distance_squared = dx*dx + dy*dy;
			if (distance_squared <= radius*radius)
				ptr[i] = color;
			else
				ptr[i] = 0;
			i++;
		}
	}
	return (ptr);
}


void	img_cpy(void *img, void *ptr, int size_line,int nb_line, int size)
{
	int	i;
	int	j;
	int	*int_img;
	int	*int_ptr;
	//printf("size line == %d\n", size_line);

	int_ptr = (int *)ptr;
	int_img = (int *)img;
	int_ptr += (nb_line * WIDTH_IMG) * (((size_line) * WIDTH_IMG)-(size_line));
	i = 0;
	j = 0;
	while (i < size * size)
	{
		//printf("i == %d et int_img == %p\n", i, int_img);
		if (int_img[i] != 0)
			int_ptr[j] = int_img[i];
		if (j == size-1)
		{
			j = 0;
			int_ptr += (size_line) * WIDTH_IMG;
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
	if (player_x < (env->mlx.win_x)/2)
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
	if (player_y < (env->mlx.win_y)/2)
	{
		index->y_start = 0;
		index->y_end = (env->mlx.win_y);
	}
	else if (env->map.height - player_y <= (env->mlx.win_y)/2)
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
	int	b;

	i = 0;
	while (i < size)
	{
		b = 0;
		//printf("i == %d \n", i);
		ptr[i] = FLOOR;
		//while (i < size && b < 8)
		//{
		//	ptr[i] = FLOOR2;
		//	i++;
		//	b++;
		//}
		//b = 0;
		//while (i < size && b < 5)
		//{
		//	printf("i == %d\n", i);
		//	ptr[i] = FLOOR;
		//	i++;
		//	b++;
		//}
		i++;
	}
	/*while (i < size)
	{
		ptr[i] = FLOOR;
		i++;
	}*/
}
//void	print_mini_map(t_env *env, char **map)
//{
//	int	*ptr;
//	int	i;
//
//	i = 0;
//	ptr = malloc(sizeof(int) * (WIDTH_IMG*WIDTH_IMG));
//	if (!ptr)
//		return (NULL);
//	while (i < WIDTH_IMG*WIDTH_IMG)
//	{
//
//		i++;
//	}
//}

void	init_full_map(t_env *env)
{
	int		i;
	int		j;
	int		count;
	char	**map;

	count = 0;
	j = 0;
	map = env->map.all_map;
	//printf("line == %d, height == %d \n", env->map.size_line, env->map.height);
	set_map(env->map.full_map, env->map.size_line*WIDTH_IMG*env->map.height*HEIGHT_IMG);
	//get_start_map(env->index, env, map);
	//printf("x_start == %d, x_end == %d, y_start == %d, y_end %d\n", index.x_start, index.x_end,index.y_start, index.y_end);
	while (/*index.y_start + j < index.y_end*/ map[j])
	{
		i = 0;
		while (map[j][i] && map[j][i] != '\n')
		{
			if (map[j][i] == '1')
				img_cpy(env->img.wall, &env->map.full_map[count*WIDTH_IMG], env->map.size_line, j, WIDTH_IMG);
			//else if (map[index.y_start + j][index.x_start + i] == '0')
			//	img_cpy(env->img.floor, &env->map.win_map[count*WIDTH_IMG], env->mlx.win_x / WIDTH_IMG, j);
			else if (map[j][i] == 'E')
				img_cpy(env->img.exit, &env->map.full_map[count*WIDTH_IMG], env->map.size_line, j, WIDTH_IMG);
			else if (map[j][i] == 'C')
				img_cpy(env->img.objet, &env->map.full_map[count*WIDTH_IMG], env->map.size_line, j, WIDTH_IMG);
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
	size = env.map.size_line*WIDTH_IMG * env.map.height*HEIGHT_IMG;
	//printf("size*SIZEIMG == %d\n", size);
	//printf("size == %d\n",  size);
	//printf("size line == %d et height == %d\n", env.map.size_line, env.map.height);
	//printf("win_size == %d\n", env.mlx.win_x*env.mlx.win_y);
	while (i < size)
	{
		//printf("i == %d\n", i);
		//printf("j == %d\n", j);
		win_map[i] = all_map[j];
		if (j == (env.map.size_line*WIDTH_IMG)-1)
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

		get_start_map(&index, env);
		printf("perso x == %d, perso y == %d\n", env->map.p_x, env->map.p_y);
		printf("decallage == %d, y start == %d et x start == %d\n", index.y_start*(env->map.size_line*WIDTH_IMG)+index.x_start, index.y_start,index.x_start);
		tmp_x = env->map.p_x - (index.x_start);
		tmp_y = env->map.p_y - (index.y_start);
		//copy_map(&env->map.full_map[index.y_start*(env->map.size_line*WIDTH_IMG)+index.x_start], env->map.win_map, *env);
		copy_map(env->map.full_map, env->map.win_map, *env);
		//set_map(env->map.win_map, env->mlx.win_x*env->mlx.win_y);
		img_cpy(env->img.perso, &env->map.win_map[tmp_y*env->mlx.win_x+tmp_x], env->mlx.win_x / WIDTH_IMG, 0, WIDTH_PLAYER);
		//print_mini_map(env, map);
		mlx_put_image_to_window(env->mlx.mlx, env->mlx.mlx_win,env->img.mlx_img, 0, 0);
}

void	print_nb_move(t_env *env)
{
	char	c;
	int		i;

	c = 8;
	i = 0;
	while (i < 15)
	{
		write(1, &c, 1);
		i++;
	}
	env->map.nb_move += 1;
	ft_putstr("nb move = ", 1);
	ft_putnbr(env->map.nb_move);
}

int	check_collision2(int player ,int case_check, int sens)
{
	int	collision;

	collision = 0;
	if (sens == HORIZON)
	{
		if ((player > case_check && player * WIDTH_PLAYER > case_check * WIDTH_IMG) || (player * WIDTH_PLAYER < case_check && player < case_check * WIDTH_IMG))
			collision = 1;
	}
	else
	{
		if ((player > case_check && player * HEIGHT_PLAYER > case_check * WIDTH_IMG) || (player * HEIGHT_PLAYER < case_check && player < case_check * WIDTH_IMG))
			collision = 1;
	}
	if (collision)
		return (1);
	return (0);
}


int	check_collision(char **map, int new_x, int new_y)
{
	int	x;
	int	y;

	x = new_x / WIDTH_IMG;
	y = new_y / WIDTH_IMG;
	if (map[y + 1][x] == '1' && check_collision2(new_y, (y + 1) * HEIGHT_IMG, VERTICAL))
		return (1);
	if (map[y][x + 1] == '1' && check_collision2(new_x, (x + 1) * WIDTH_IMG, HORIZON))
		return (1);
	if (map[y + 1][x + 1] == '1' && check_collision2(new_x, (x + 1) * WIDTH_IMG, HORIZON) && check_collision2(new_y, (y + 1) * HEIGHT_IMG, VERTICAL))
		return (1);
	if (map[y - 1][x] == '1' && check_collision2(new_y, (y - 1) * HEIGHT_IMG,VERTICAL))
		return (1);
	if (map[y][x - 1] == '1' && check_collision2(new_x, (x - 1) * WIDTH_IMG, HORIZON))
		return (1);
	if (map[y - 1][x - 1] == '1' && check_collision2(new_x, (x - 1) * WIDTH_IMG, HORIZON) && check_collision2(new_y, (y - 1) * HEIGHT_IMG,VERTICAL))
		return (1);
	if (map[y - 1][x + 1] == '1' && check_collision2(new_x, (x + 1) * WIDTH_IMG, HORIZON) && check_collision2(new_y, (y - 1) * HEIGHT_IMG,VERTICAL))
		return (1);
	if (map[y + 1][x - 1] == '1' && check_collision2(new_x, (x - 1) * WIDTH_IMG, HORIZON) && check_collision2(new_y, (y + 1) * HEIGHT_IMG,VERTICAL))
		return (1);
	return (0);
}

int	handle_key(t_env *env)
{
	char	**map;
	t_pos	pos;

	if (!env->key.up && !env->key.down && !env->key.left && !env->key.right)
		return (0);
	if ((env->key.up && env->key.down) || (env->key.left && env->key.right))
		return (0);
	//printf("dans handle key == r == %d, l == %d, up == %d, d == %d\n" , env->key.right, env->key.left, env->key.up,env->key.down);
	map = env->map.all_map;
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
//	if (check_collision(map, pos.new_x, pos.new_y))
//		return (0);
	env->map.p_x = pos.new_x;
	env->map.p_y = pos.new_y;
	load_map(env);
	print_nb_move(env);
	//print_map(map);
	if (!env->map.nb_collectible && map[pos.new_y][pos.new_x] == 'p')
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
	if (key_code == 65363)
		env->key.right = 0;
	else if (key_code == 65362)
		env->key.up = 0;
	else if (key_code == 65361)
		env->key.left = 0;
	else if (key_code == 65364)
		env->key.down = 0;
	//printf("dans key release key code = %d== r == %d, l == %d, up == %d, d == %d\n" , key_code , env->key.right, env->key.left, env->key.up,env->key.down);
	return (key_code);
}

int	handle_keypress(int key_code,	t_env *env)
{
	env->key.loop_count += 1;
	if (key_code == 65307)
		exit(0);
	if (key_code == 65363)
		env->key.right = 1;
	else if (key_code == 65362)
		env->key.up = 1;
	else if (key_code == 65361)
		env->key.left = 1;
	else if (key_code == 65364)
		env->key.down = 1;
	//handle_key(env);
	//printf("dans keypress keycode = %d == r == %d, l == %d, up == %d, d == %d\n" ,key_code, env->key.right, env->key.left, env->key.up,env->key.down);
	return (key_code);
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
	env.map.p_x *= WIDTH_IMG;
	env.map.p_y *= WIDTH_IMG;
	if (!verif_wall(env.map.all_map))
		return (1);
	get_map_size(&env);
	env.img.mlx_img = (int *)mlx_new_image(env.mlx.mlx, env.mlx.win_x, env.mlx.win_y);
	if (!env.img.mlx_img)
		return 1;
	env.map.win_map = (int *)mlx_get_data_addr(env.img.mlx_img, &bpp, &size_line, &endian);

	env.img.wall = init_square(0x778899, WIDTH_IMG);
	env.img.exit = init_square(EXIT, WIDTH_IMG);
	env.img.perso = init_square(PLAYER, WIDTH_PLAYER);
	env.img.objet = init_circle(OBJET);
	env.img.floor = init_square(FLOOR, WIDTH_IMG);
	if (!env.img.wall || !env.img.exit || !env.img.perso || !env.img.objet || !env.img.floor)
		return (free_struct(&env), printf("coucou le malloc rate\n"),0);
	env.mlx.mlx_win = mlx_new_window(env.mlx.mlx, env.mlx.win_x, env.mlx.win_y, "so_long");
	printf("img main == %p\n", env.img.wall);
	init_full_map(&env);
	load_map(&env);
	if (!env.mlx.mlx_win)
		return (free_struct(&env), 1);
	mlx_hook(env.mlx.mlx_win, 17, 0, mlx_close, &env);
	mlx_hook(env.mlx.mlx_win, 3, 1L<<1, handle_keyrelease, &env);
	mlx_hook(env.mlx.mlx_win, 2, 1L<<0, handle_keypress, &env);
	mlx_loop_hook(env.mlx.mlx, &handle_key, &env);
	mlx_loop(env.mlx.mlx);
}