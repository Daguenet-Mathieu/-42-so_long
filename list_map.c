/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:25:43 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/31 20:24:33 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	lst_clear(t_list **list)
{
	t_list	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = tmp;
	}
}

char	**convert_list(t_list **tmp_map)
{
	char	**map;
	int		size;
	int		i;
	t_list	*tmp;

	i = 0;
	size = lst_size(*tmp_map);
	map = malloc(sizeof(char *) * (size + 1));
	if (!map)
		return (lst_clear(tmp_map), NULL);
	while (i < size)
	{
		map[i] = (*tmp_map)->content;
		i++;
		tmp = (*tmp_map)->next;
		free(*tmp_map);
		*tmp_map = tmp;
	}
	map[i] = NULL;
	return (map);
}
