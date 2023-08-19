#include "so_long.h"

# ifndef HEIGHT
#  define HEIGHT  7
# endif

# ifndef WIDTH
#  define WIDTH  16
# endif

int	get_rand_int(unsigned int *tab, unsigned int size)
{
	int	fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (0);
	if (read(fd, tab, size * sizeof(int)) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

void	init_size(unsigned int tab[4], unsigned int size[2])
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (i < 4)
	{
		if (tab[i] % 2)
			nb += 1;
		i++;
	}
	if (nb <= 1 || (nb == 2 && (((tab[0] % 2) && (tab[3] % 2)) || ((tab[1] % 2) && (tab[2] % 2)))))
	{
		size[0] = 1;
		return ;
	}
	if (tab[0] % 2 || tab[1] % 2)
		size[0] = 1;
	if (tab[2] % 2 || tab[3] % 2)
		size[1] = 1;
	if (tab[0] % 2 && tab[1] % 2)
		size[0] += 1;
	if (tab[2] % 2 && tab[3] % 2)
		size[1] += 1;
}
/*
void	init_map_info(int tab[4], t_info *info, int i)
{
	if (i == 0)
		info = fill_info(0, 0, tab[i + 1] % 2, tab[i + 2] % 2);
	if (i == 1)
		info = fill_info(0, tab[i - 1] % 2, tab[i + 2] % 2, 0);
	if (i == 2)
		info = fill_info(0, 0, tab[i + 1] % 2, tab[i + 2] % 2);
	if (i == 3)
		info = fill_info(0, 0, tab[i + 1] % 2, tab[i + 2] % 2);
}*/

void	fill_room(int width, int height, char **room)
{
	int		i;
	int		j;

	i = 0;
	while (i < height)
	{	
		j = 0;
		while (j < width)
		{
			if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
				room[i][j] = '1';
			else
				room[i][j] = '0';
			j++;
		}
		i++;
	}
	room[height / 2][width / 2] = 'P';
}

void set_wall(char **map)
{
	int	i;
	int	j;

	j = 1;
	while (map[j + 1])
	{
		i = 1;
		while (map[j][i + 1])
		{
			if (map[j][i] == '2' && map[j + 1][i] == '0')
				map[j][i] = '1';
			else if (map[j][i] == '0' && map[j + 1][i] == '2')
				map[j][i] = '1';
			i++;
		}
		j++;
	}
}

void	fill_curved_room(unsigned int tab[4], char **room)
{
	int	i;
	int	k;
	int	c;
	int	j;

	j = 0;
	c = 0;
	i = 0;
	if (!(tab[1] % 2))
		c = WIDTH;
	else
		c = WIDTH * 2;
	if (!(tab[0] % 2))
		j = WIDTH;
	while (i < HEIGHT)
	{
		k = j;
		room[i][k++] = '1';
		while (k < c)
		{
			if (i == 0 || i == HEIGHT - 1 || k == c - 1)
				room[i][k++] = '1';
			else
				room[i][k++] = '0';
		}
		i++;
	}
	room[i / 2][c / 2 + 1] = 'P';
	j = 0;
	c = 0;
	i = HEIGHT;
	if (!(tab[3] % 2))
		c = WIDTH;
	else
		c = WIDTH * 2;
	if (!(tab[2] % 2))
		j = WIDTH;
	while (i < HEIGHT * 2)
	{
		k = j;
		room[i][k++] = '1';
		while (k < c)
		{
			if (i == HEIGHT * 2 - 1 || k == c - 1)
				room[i][k++] = '1';
			else
				room[i][k++] = '0';
		}
		i++;
	}
	j = 1;
	while (room[HEIGHT - 1][j + 1])
	{
		if (room[HEIGHT][j] != '2' && room[HEIGHT - 2][j] != '2' && room[HEIGHT][j] != '1' && room[HEIGHT - 2][j] != '1')
			room[HEIGHT - 1][j]= '0';
		j++;
	}
	set_wall(room);
}


int	alloc_room(unsigned int tab[4], unsigned int size[2], char ***room)
{
	int	i;
	int	j;
	int	width;
	int	height;

	i = 0;
	width = WIDTH;
	height = HEIGHT;
	if (size[0] == 2 || size[1] == 2)
		width *= 2;
	if (size[0] && size[1])
		height *= 2;
	*room = malloc(sizeof(char *) * (height + 1));
	if (!*room)
		return (0);
	while (i < height)
	{
		j = 0;
		(*room)[i] = malloc(sizeof(char) * (width + 2));
		//if (!(*room)[i])
		//	return (free_tab(*room), 0);
		while(j < width)
			(*room)[i][j++] = '2';
		(*room)[i][j] = 0;
		i++;
	}
	(*room)[i] = NULL;
	if ((size[0] == size[1]) || (!size[0] && size[1]) || (!size[1] && size[0]))
		fill_room(width, height, *room);
	else
		fill_curved_room(tab, *room);
	return (1);
}

char	**get_room()
{
	unsigned int	tab[4];
	unsigned int	size[2];
	char	**room;

	size[0] = 0;
	size[1] = 0;
	if (!get_rand_int(tab, 4))
		return (NULL);
	init_size(tab, size);
	if (!alloc_room(tab, size, &room))
		return (NULL);
	//print_map_2(room);
	return (room);
}

int main()
{
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());
	print_map_2(get_room());

}