#ifndef FLOOD_FILL_H
# define FLOOD_FILL_H

#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>


# ifndef TOP
#  define TOP 1
# endif

# ifndef DOWN
#  define DOWN 2
# endif

# ifndef LEFT
#  define LEFT 3
# endif

# ifndef RIGHT
#  define RIGHT 4
# endif

typedef struct	s_fill
{
	int top;
	int	down;
	int	right;
	int	left;
	int	x;
	int	y;
	struct s_fill *next;
	struct s_fill *prev;
}				t_fill;

typedef struct	s_fill_env
{
	t_fill	*last_fill;
	t_fill	*new;
	int		new_x;
	int		new_y;
}				t_fill_env;

void    flood_fill(int x, int y, char **map);
void	check_direction(t_fill_env *fill);
void	clear_fill(t_fill **last_fill);
int		check_fill(t_fill *fill);
void	free_fill(t_fill **last_fill);
void	init_coordonnees(t_fill **last_fill, int sens, int *x, int *y);
void	add_to_fill(t_fill *new, t_fill **last_fill);
t_fill	*init_fill(int x, int y);

#endif