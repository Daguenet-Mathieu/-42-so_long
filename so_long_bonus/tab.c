/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:27:05 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/01 21:31:40 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**cpy_map(char **map)
{
	char	**new_map;
	int		i;
	int		j;

	j = 0;
	new_map = malloc(sizeof(char *) * (tab_size(map) + 1));
	if (!new_map)
		return (ft_error("alloc cpy map\n"), NULL);
	while (map[j])
	{
		i = 0;
		new_map[j] = malloc(ft_strlen(map[j]) + 1);
		if (!new_map[j])
			return (free_tab(new_map), ft_error("alloc cpy line\n"), NULL);
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

int	tab_size(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
