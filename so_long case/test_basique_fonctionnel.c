/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:32:16 by madaguen          #+#    #+#             */
/*   Updated: 2023/04/12 14:20:00 by madaguen         ###   ########.fr       */
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

typedef struct s_coucou
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
}		t_coucou;

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

t_list	*lst_new(char *s)
{
	t_list	*new;
	
	new = malloc(sizeof(t_list));
	if (!new)
		return (printf("fail, ?\n"), NULL);
	printf("ici, new? %p, \n", new);
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
	printf("list = %p\n", *list);
	if (!*list)
	{
		printf("list = %p\n", *list);
		*list = new;
		return ;
	}
	printf("tmp nexxt avant boucle = %p\n", tmp->next);
	while (tmp->next)
	{
		printf("list boucle = %p\n", tmp);
		printf("tmp nexxt dans boucle = %p\n", tmp->next);
		tmp = tmp->next;
	}
	tmp->next = new;
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
		printf("line = %p\n", line);
            	if(!line)
			a = 0;
		new = lst_new(line);
		if (!new)
			return (printf("ici? a = %d\n", a), NULL);
		add_back(&tmp_map, new);
	}
	printf("ici?\n");
	map = convert_list(&tmp_map);
	return (map);
}

void	put_img(t_coucou *test, int h, int v, int *old_x, int *old_y)
{
	printf("old = %d, %d\n", *old_x, *old_y);
	printf("h = %d, x = %d y = %d v= %d\n", h, test->size_x, test->size_y, v);
	if (test->map[v/64][h/64] == '1')
		return;
	if (test->map[*old_y/64][*old_x/64] == 'e')
		mlx_put_image_to_window(test->mlx, test->mlx_win, test->red, *old_x, *old_y);
	else
		mlx_put_image_to_window(test->mlx, test->mlx_win, test->grass, *old_x, *old_y);
	if (test->map[v/64][h/64] == 'c')
	{
		test->collected += 1;
		test->map[v/64][h/64] = 0;
		printf("total = %d actuel = %d\n", test->nb_collectible, test->collected);
	}
	if (test->map[v/64][h/64] == 'e' && test->nb_collectible == test->collected)
	{
		printf("victoire\n");
		exit(0);
	}
	mlx_put_image_to_window(test->mlx, test->mlx_win, test->blue, h, v);
	*old_x = h;
	*old_y = v;	
}
		
void init_img(t_coucou *test, char **map)
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
			printf("map[j][i]= %c\n", map[j][i]);
			if (map[j][i] == '0')
				mlx_put_image_to_window(test->mlx, test->mlx_win, test->grass, x, y);
			if (map[j][i] == '1')
				mlx_put_image_to_window(test->mlx, test->mlx_win, test->white, x, y);
			if (map[j][i] == 'p')
			{
				mlx_put_image_to_window(test->mlx, test->mlx_win, test->blue, x, y);
				test->pos_x = x;
				test->pos_y = y;
				printf("pos = %d, %d\n", test->pos_x, test->pos_y);
			}
			if (map[j][i] == 'c')
				mlx_put_image_to_window(test->mlx, test->mlx_win, test->yellow, x, y);
		
			if (map[j][i] == 'e')
				mlx_put_image_to_window(test->mlx, test->mlx_win, test->red, x, y);			
			x+=64;
			i++;
		}
		y +=64;
		j++;
	}
}

int	key_cook(int key_code, t_coucou *test)
{
	int	h = test->pos_x;
	int	v = test->pos_y;

	printf("total = %d actuel = %d\n", test->nb_collectible, test->collected);
	if (key_code == 65363)
		h+=64;

	else if (key_code == 65361)
		h-=64;
	else if (key_code == 65364)
		v+=64;
	else if (key_code == 65362)
		v-=64;
	else
		return (printf("touche pas prise en compte = %d\n", key_code));
	if (v < 64 || h < 64 || h >= test->size_x - 64 || v >= test->size_y - 64)
		return (0);
	printf("key_cook %d , %d\n", h ,v);
	put_img(test, h, v, &test->pos_x, &test->pos_y);
	return (printf("touche = %d\n", key_code));
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

int	main(int ac, char **av)
{
	(void) ac;
	(void) av;
	t_coucou test;
	int	un;
	int	deux;
	int	v;
	int	h;
	
	test.collected = 0;
	v = 1;
	h = 1;
	if (ac != 2)
		return (0);
	test.map = get_map(av[1]);
	test.nb_collectible = get_map_nb(test.map, 'c');
	if (!test.map)
		return (printf("fail map \n"));
	test.mlx = mlx_init();
	if (!test.mlx)
		return (printf("zut1\n"));
	test.size_x = (ft_strlen(test.map[0]) - 1) * 64;
	test.size_y = tab_size(test.map) * 64;
	printf("size = %d, %d\n", test.size_x, test.size_y);
	test.mlx_win = mlx_new_window(test.mlx, test.size_x, test.size_y, "so_long");
	if (!test.mlx_win)
		return (printf("zut2\n"));
	test.blue = mlx_xpm_file_to_image(test.mlx, "Puny-Characters/Environment/blue.xpm", &un, &deux);
	test.grass = mlx_xpm_file_to_image(test.mlx, "Puny-Characters/Environment/Grass2.xpm", &un, &deux);
	test.white = mlx_xpm_file_to_image(test.mlx, "Puny-Characters/Environment/white.xpm", &un, &deux);
	test.red = mlx_xpm_file_to_image(test.mlx, "Puny-Characters/Environment/red.xpm", &un, &deux);
	test.yellow = mlx_xpm_file_to_image(test.mlx, "Puny-Characters/Environment/yellow.xpm", &un, &deux);
	printf("test.red = %p, test.yellow = %p, test.blue = %p, test.grass = %p, test.white = %p\n", test.red, test.yellow, test.blue, test.grass, test.white);
	if (!test.blue || !test.grass || !test.white || !test.red || !test.yellow)
		return (printf("zut3\n")); //mlx destroy image pour CELUI QUI A REUSSI
	init_img(&test, test.map);
	mlx_hook(test.mlx_win, 2, 1L<<0, key_cook, &test);
	mlx_loop(test.mlx);
}
