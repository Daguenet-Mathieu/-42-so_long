# ifndef MAP_H
# define MAP_H

# ifndef HEIGHT
#  define HEIGHT  8
# endif

# ifndef WIDTH
#  define WIDTH  15
# endif

typedef struct s_info
{
    int top;
    int left;
    int dowwn;
    int right;
}			t_info;

void	print_map_2(char **map);
#endif