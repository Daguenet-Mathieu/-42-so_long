/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:26:50 by madaguen          #+#    #+#             */
/*   Updated: 2023/09/01 21:15:20 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**get_map(char *file_name)
{
	t_list	*tmp_map;
	t_list	*new;
	char	**map;
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (ft_error("fail open\n"), NULL);
	tmp_map = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		new = lst_new(line);
		if (!new)
			return (lst_clear(&tmp_map), NULL);
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
	if (len2 == -1 && s[len + 1] == '.')
		return (1);
	else
		return (0);
}

int	get_map_nb(char **map, char c)
{
	int	i;
	int	j;
	int	nb;

	nb = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
				nb += 1;
			j++;
		}
		i++;
	}
	return (nb);
}

int	check_nb_elem(t_env *env)
{
	char	**map;

	map = env->map.all_map;
	env->map.nb_collectible = get_map_nb(map, 'C');
	if (!env->map.nb_collectible)
		return (0);
	if (get_map_nb(map, 'P') != 1 || get_map_nb(map, 'E') != 1)
		return (0);
	return (1);
}

int	verif_wall(char **map)
{
	int	i;
	int	j;
	int	l;

	j = -1;
	l = ft_strlen(map[0]);
	while (map[++j])
	{
		i = 0;
		if ((j > 0 && map[j + 1]) && (map[j][0] != '1' \
		|| map[j][l - 2] != '1'))
			return (0);
		if ((map[j + 1]) && (map[j][0] != '1' && map[j][l - 2] != '1'))
			return (0);
		while (i < l - 2)
		{
			if (j == 0 && map[j][i] != '1')
				return (0);
			if (!map[j + 1] && (map[j][i] != '1'))
				return (0);
			i++;
		}
	}
	return (1);
}
