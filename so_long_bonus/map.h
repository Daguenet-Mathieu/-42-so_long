# ifndef MAP_H
# define MAP_H

typedef struct s_info
{
    int top;
    int left;
    int dowwn;
    int right;
}			t_info;

void	print_map_2(char **map);
#endif