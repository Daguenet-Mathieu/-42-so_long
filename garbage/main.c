/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:32:16 by madaguen          #+#    #+#             */
/*   Updated: 2023/05/04 21:04:38 by madaguen         ###   ########.fr       */
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

# ifndef SIZE_IMG
#  define SIZE_IMG 32
# endif

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*blue;
	void	*grass;
	void	*white;
	void	*red;
	void	*yellow;
	int	size_x;
	int	size_y;
	char	**map;
	int	pos_x;
	int	pos_y;
	int	nb_collectible;
	int	collected;
	int	nb_move;
}		t_mlx;

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

void	free_struct(t_mlx *var_mlx)
{
	if (var_mlx->mlx)
		free(var_mlx->mlx);
}

typedef struct s_list
{
	char	*content;
	struct s_list *next;
}		t_list;

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
	while (s && s[i])
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

int	verif_wall(char **map, int	tab_size)
{
	int	i;
	int	j;
	int	size;
	int	tmp_size;

	j = 0;
	size = ft_strlen(map[j]);
	while (map[j])
	{
		i = 0;
		tmp_size = ft_strlen(map[j]);
		if (size != tmp_size)
			return (0);
		while (map[j][i])
		{
			if ( (j == 0 || j == tab_size) && map[j][i] != 1)
				return (0);
			if ((j != 0 || j!= tab_size) && (map[j][0] != 1 || map[j][tmp_size - 2] != 1))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

void	get_index(char **tab, int *j, int *i, char c)
{
	*j = 0;
	while(tab[*j])
	{
		*i = 0;
		while (tab[*j][*i])
		{
			if (tab[*j][*i] == c)
				return ;
			(*i)++;
		}
	}
}

int	check_map(int j, int i, char **map)
{
	if (map[j][i] != 'p')
		return (0);
	return (0);
}

int	verif_map(char **map)
{
	int	i;
	int	j;

	get_index(map, &j, &i, 'p');
	return (check_map(j, i, map));
}

void	ft_putstr(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	ft_error(char *s)
{
	ft_putstr(s, 22);
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

void	put_img(t_mlx *test, int h, int v, int *old_x, int *old_y)
{
	if (test->map[v/SIZE_IMG][h/SIZE_IMG] == '1')
		return;
	if (test->map[*old_y/SIZE_IMG][*old_x/SIZE_IMG] == 'e')
		mlx_put_image_to_window(test->mlx, test->mlx_win, test->red, *old_x, *old_y);
	else
		mlx_put_image_to_window(test->mlx, test->mlx_win, test->grass, *old_x, *old_y);
	if (test->map[v/SIZE_IMG][h/SIZE_IMG] == 'c')
	{
		test->collected += 1;
		test->map[v/SIZE_IMG][h/SIZE_IMG] = 0;
	}
	if (test->map[v/SIZE_IMG][h/SIZE_IMG] == 'e' && test->nb_collectible == test->collected)
	{
		ft_putstr("victoire\n", 1);
		exit(0);
	}
	mlx_put_image_to_window(test->mlx, test->mlx_win, test->blue, h, v);
	*old_x = h;
	*old_y = v;	
	test->nb_move++;
	ft_putstr("move count = ", 1);
	ft_putnbr(test->nb_move);
	write(1, "\n", 1);
}
		
void init_img(t_mlx *test, char **map)
{
	int	i;
	int	j;
	int	x;
	int	y;
	
	y = 0;
	j = 0;
	while (map[j])
	{
		i = 0;
		x = 0;
		while (map[j][i])
		{
			if (map[j][i] == '0')
				mlx_put_image_to_window(test->mlx, test->mlx_win, test->grass, x, y);
			if (map[j][i] == '1')
				mlx_put_image_to_window(test->mlx, test->mlx_win, test->white, x, y);
			if (map[j][i] == 'p')
			{
				mlx_put_image_to_window(test->mlx, test->mlx_win, test->blue, x, y);
				test->pos_x = x;
				test->pos_y = y;
			}
			if (map[j][i] == 'c')
				mlx_put_image_to_window(test->mlx, test->mlx_win, test->yellow, x, y);
		
			if (map[j][i] == 'e')
				mlx_put_image_to_window(test->mlx, test->mlx_win, test->red, x, y);			
			x+= SIZE_IMG;
			i++;
		}
		y += SIZE_IMG;
		j++;
	}
}

int	key_cook(int key_code, t_mlx *test)
{
	int	h = test->pos_x;
	int	v = test->pos_y;

	if (key_code == 65307)
		exit(0);
	if (key_code == 65363)
		h+=SIZE_IMG;

	else if (key_code == 65361)
		h-=SIZE_IMG;
	else if (key_code == 65364)
		v+=SIZE_IMG;
	else if (key_code == 65362)
		v-=SIZE_IMG;
	if (v < SIZE_IMG|| h < SIZE_IMG|| h >= test->size_x - SIZE_IMG|| v >= test->size_y - SIZE_IMG)
		return (0);
	put_img(test, h, v, &test->pos_x, &test->pos_y);
	return (key_code);
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

// int	check_map_name(char *s, char *s2)
// {
// 	int	len;
// 	int	len2;

// 	len = ft_strlen(s) - 1;
// 	len2 = ft_strlen(s2) - 1;
// 	while (len >= 0 || len2 >= 0)
// 	{
// 		if (s2[len] != s2[len2])
// 			return (0);
// 		len--;
// 		len2--;
// 	}
// 	if (len2 == 0)
// 		return (1);
// 	else
// 		return (0);
// }

int	mlx_close(t_mlx mlx_var)
{
	(void) mlx_var;
		exit(0);
	return (0);
}

int	main(int ac, char **av)
{
	(void) ac;
	(void) av;
	t_mlx mlx_var;
	int	un;
	int	deux;
	int	v;
	int	h;
	
	mlx_var.collected = 0;
	v = 1;
	h = 1;
	if (ac != 2)
		return (0);
	mlx_var.map = get_map(av[1]);
	mlx_var.nb_collectible = get_map_nb(mlx_var.map, 'c');
	if (!mlx_var.map)
		return (1);
	mlx_var.mlx = mlx_init();
	if (!mlx_var.mlx)
		return (1);
	mlx_var.nb_move = 0;
	mlx_var.size_x = (ft_strlen(mlx_var.map[0]) - 1) * SIZE_IMG;
	mlx_var.size_y = tab_size(mlx_var.map) * SIZE_IMG;
	mlx_var.mlx_win = mlx_new_window(mlx_var.mlx, mlx_var.size_x, mlx_var.size_y, "so_long");
	if (!mlx_var.mlx_win)
		return (1);
	if (SIZE_IMG == 32)
	{
		mlx_var.blue = mlx_xpm_file_to_image(mlx_var.mlx, "images/blue.xpm", &un, &deux);
		mlx_var.grass = mlx_xpm_file_to_image(mlx_var.mlx, "images/Grass2.xpm", &un, &deux);
		mlx_var.white = mlx_xpm_file_to_image(mlx_var.mlx, "images/white.xpm", &un, &deux);
		mlx_var.red = mlx_xpm_file_to_image(mlx_var.mlx, "images/red.xpm", &un, &deux);
		mlx_var.yellow = mlx_xpm_file_to_image(mlx_var.mlx, "images/yellow.xpm", &un, &deux);
	}
	else
	{
		mlx_var.blue = mlx_xpm_file_to_image(mlx_var.mlx, "images/isaac64.xpm", &un, &deux);
		mlx_var.grass = mlx_xpm_file_to_image(mlx_var.mlx, "images/Grass64.xpm", &un, &deux);
		mlx_var.white = mlx_xpm_file_to_image(mlx_var.mlx, "images/white64.xpm", &un, &deux);
		mlx_var.red = mlx_xpm_file_to_image(mlx_var.mlx, "images/red64.xpm", &un, &deux);
		mlx_var.yellow = mlx_xpm_file_to_image(mlx_var.mlx, "images/yellow64.xpm", &un, &deux);
	}
	if (!mlx_var.blue || !mlx_var.grass || !mlx_var.white || !mlx_var.red || !mlx_var.yellow)
		return (/*free_struct(mlx_var),*/1); //mlx destroy image pour CELUI QUI A REUSSI
	init_img(&mlx_var, mlx_var.map);
	mlx_hook(mlx_var.mlx_win, 2, 1L<<0, key_cook, &mlx_var);
	mlx_hook(mlx_var.mlx_win, 17, 0, mlx_close, &mlx_var);
	mlx_loop(mlx_var.mlx);
}
