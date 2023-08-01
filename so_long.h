# ifndef SO_LONG_H
# define SO_LONG_H

#include "mlx_linux/mlx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line/get_next_line.h"
#include "flood_fill/flood_fill.h"
#include "image.h"

# ifndef SPEED
#  define SPEED  8
# endif

# ifndef BEFORE
#  define BEFORE  0
# endif

# ifndef AFTER
#  define AFTER  1
# endif

typedef struct	s_case
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	area_in_case;
}				t_case;

typedef struct	s_iter
{
	int			i;
	int			j;
	int			c;
	int			count;
	char		**map;

}				t_iter;

typedef struct	minimap
{
	int	*minimap;
	int	size_line;
	int	nb_line;
	int	active;
}	t_minimap;

typedef struct	s_index
{
	int	x_start;
	int	x_end;
	int	y_start;
	int	y_end;
}				t_index;

typedef struct s_key
{
	int	up;
	int	down;
	int	left;
	int	right;
}				t_key;

typedef struct	s_pos
{
		int		y;
		int		x;
		int		new_y;
		int		new_x;
		int		sens_x;
		int		sens_y;
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

typedef struct	s_obj
{
			int	x;
			int	y;
			int	i;
			int	j;

}				t_obj;

typedef struct	s_map
{
		char	**all_map;
		int		*win_map;
		int		*full_map;
		int		nb_collectible;
		int		nb_move;
		int		p_x;
		int		p_y;
		t_obj	*objets;
		int		height;
		int		size_line;
}				t_map;

typedef struct	s_img
{
	int			*img;
	int			size;
	int			height;
	int			width;
}				t_img;

typedef struct	s_img_list
{
		t_img	wall;
		t_img	objet;
		t_img	exit;
		t_img	perso;
		void	*mlx_img;
}				t_img_list;

typedef struct		s_env
{
		t_img_list	img;
		t_mlx		mlx;
		t_map		map;	
		t_key		key;
		t_pos		pos;
		t_index		index;
		t_minimap	minimap;
		int			loop;
}					t_env;


typedef struct s_list
{
	char	*content;
	struct s_list *next;
}		t_list;

void	ft_putnbr(int n);
void	ft_putstr(char *s, int fd);
void	ft_error(char *s);
int		ft_strlen(char *s);
int		tab_size(char **map);
int		lst_size(t_list *a);
t_list	*lst_new(char *s);
char	**convert_list(t_list **tmp_map);
void	add_back(t_list **list, t_list *new);
void	free_tab(char **tab);
char	**cpy_map(char **map);
char	**get_map(char *file_name);
int		check_map_name(char *s, char *s2);
int		get_map_nb(char **map, char c);
int		check_nb_elem(t_env *env);
void	free_struct(t_env *env);
int		verif_wall(char **map);
int		mlx_close(t_env *env);
void	init_struct(t_env *env);
void	get_player_pos(char **map, int *x, int *y);
void	print_map(char **map);
void	*init_square(int color, int size);
void	*init_circle(int color, int radius);
void	img_cpy(t_img img, int *ptr, int size_line, int nb_line);
void	fill_minimap(int color, int	*map, int size_line, int width);
void	set_minimap(t_minimap *minimap, char **map);
void	set_minimap_util(t_minimap *minimap, char **map, int i, int j);
void	copy_minimap(t_env env, int *minimap, int *map);
void	print_mini_player(t_env env);
void	set_x_start(t_index *index, t_env *env);
void	set_y_start(t_index *index, t_env *env);
void	get_start_map(t_index *index, t_env *env);
void	set_map(int *ptr, int size_line, int size_img_line, int nb_img_line);
void	set_ptr(t_env *env, t_iter iter, int *c);
void	init_full_map(t_env *env);
void	copy_map(int *all_map, int *win_map, t_env env);
void	load_map(t_env *env);
void	print_nb_move(t_env *env);
void	delete_obj(t_obj *obj, int size);
void	remove_collectible(t_env *env, int i, int j);
int		in_case_y(t_pos pos, int c_y, int size);
int		player_in_case(t_pos pos, t_case this_case, int pixel);
int		verif_case(t_env *env, t_pos pos, char c, t_case this_case);
void	init_zone(t_case zone[4], t_pos pos);
int		check(t_env *env, t_pos pos, char c);
void	init_pos_l_r(t_pos *pos, t_env *env, int *move);
void	init_pos_t_d(t_pos *pos, t_env *env, int *move);
void	do_move(t_pos pos, t_env *env, int *player, int new_pos);
int		handle_key(t_env *env);
void	get_map_size(t_env *env);
void	ajust_key_release(int *key1, int *key2);
int		handle_keyrelease(int key_code, t_env *env);
void	ajust_key_press(int *key1, int *key2);
int		handle_keypress(int key_code, t_env *env);
void	init_struct_img(t_img *img, int height, int width);
int		init_img(t_env *env);
t_obj	*init_pos_obj(char **map, t_env env);
void	set_hooks_mlx(t_env *env);
int		verif_map(t_env *env);
int		check_arg(int size, char *arg);
void	init_info(t_env *env);
int		init_map(t_env *env);
int		map(t_env *env, char *arg);
int		init_minimap(t_env *env);

#endif