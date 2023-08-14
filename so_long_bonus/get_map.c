#include"so_long.h"

# ifndef HEIGHT
#  define HEIGHT  7
# endif

# ifndef WIDTH
#  define WIDTH  16
# endif

int	get_rand_int(unsigned int *tab, unsigned int size)
{
	int	i;
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

void	init_size(int tab[4], int size[4])
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
	if (nb <= 1 || nb == 2 && (((tab[0] % 2) && (tab[3] % 2)) || ((tab[1] % 2) && (tab[2] % 2))))
	{
		size[0] = HEIGHT;
		size[1] = HEIGHT;
		size[2] = WIDTH;
		size[3] = WIDTH;
		return ;
	}
	if (tab[0] % 2 && !(tab[2] % 2))
		size[0] = HEIGHT;
	if (tab[2] % 2)
		size[0] = HEIGHT * 2;
	if ((tab[1] % 2) && !(tab[3] % 2))
		size[1] = HEIGHT;
	if (tab[3] % 2)
		size[1] = HEIGHT * 2;
	if ((tab[0] % 2) && !(tab[1] % 2))
		size[2] = WIDTH;
	if (tab[1] % 2)
		size[2] = WIDTH * 2;
	if ((tab[2] % 2) && !(tab[3] % 2))
		size[3] = WIDTH;
	if (tab[3] % 2)
		size[3] = WIDTH * 2;
}

int	alloc_room(int tab[4], int size[2], char ***room)
{
	int	i;
	int	j;
	int	width;
	int	height;

	i = 0;
	if (size[0] >= size[1])
		height = size[0];
	else
		height = size[1];
	if (size[2] >= size[3])
		width = size[2];
	else
		width = size[3];
	printf("height == %d et %d et width == %d et %d\n", size[0], size[1], size[2], size[3]);
	*room = malloc(sizeof(char *) * (height + 1));
	if (!*room)
		return (0);
	while (i < size[1])
	{
		j = 0;
		(*room)[i] = malloc(sizeof(char) * (width + 1));
		//if (!(*room)[i])
		//	free_tab(*room);
		while(j < width)
			(*room)[i][j++] = '2';
		(*room)[j] = 0;
		i++;
	}
	(*room)[i] = NULL;
	//	fill_room(size, tab, room);
}
/*
void	fill_room(int size[2], int tab[4], char **room)
{
	if (tab[0])
		fill();
	if (tab[1])
	if (tab[2])
	if (tab[3])
}*/

char	**get_room()
{
	unsigned int	tab[4];
	unsigned int	size[4];
	char	**room;

	size[0] = 7;
	size[1] = 7;
	size[2] = 16;
	size[3] = 16;
	if (!get_rand_int(tab, 4))
		return (NULL);
	init_size(tab, size);
	if (!alloc_room(tab, size, &room))
		return (NULL);
	return (room);
}

int main()
{
	get_room();
	get_room();
	get_room();
	get_room();
	get_room();
	get_room();
	get_room();
	get_room();
}