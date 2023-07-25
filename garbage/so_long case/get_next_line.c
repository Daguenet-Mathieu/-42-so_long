/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:48:44 by madaguen          #+#    #+#             */
/*   Updated: 2023/04/12 21:09:57 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clear_lst(t_lst *start)
{
	t_lst	*tmp;

	while (start)
	{
		tmp = start->next;
		free(start->content);
		free(start);
		start = tmp;
	}
}

void	cpy_lst(char **line, char **buf, t_stock stock)
{
	int	index[4];

	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	index[3] = 0;
	if (stock.c == 0)
	{
		free(*buf);
		*buf = NULL;
	}
	while (stock.start)
	{
		while (stock.start->content[index[0]] && index[2] <= stock.size)
			(*line)[index[2]++] = stock.start->content[index[0]++];
		while (*buf && stock.start->content[index[0]]
			&& stock.start->content[index[0] + index[1]])
			(*buf)[index[3]++] = stock.start->content[index[0] + index[1]++];
		stock.start = stock.start->next;
		index[0] = 0;
	}
	if (*buf)
		(*buf)[index[3]] = 0;
	(*line)[index[2]] = 0;
}

void	lst_new_add(t_lst **start, t_lst **last, char *tmp)
{
	t_lst	*new;

	new = malloc(sizeof(t_lst));
	if (!new)
		return (clear_lst(*start));
	new->next = NULL;
	new->content = tmp;
	if (*start == NULL)
		*last = *start;
	if (!*start)
	{
		*start = new;
		*last = *start;
	}
	else
	{
		(*last)->next = new;
		*last = new;
	}
}

void	ft_init_strs(char **buf, t_stock *stock)
{
	stock->i = 0;
	stock->c = 0;
	stock->nl = 0;
	if (!stock->tmp && !stock->start)
		return ;
	while (stock->tmp && (stock->tmp[stock->i]
			&& stock->tmp[stock->i] != '\n'))
		stock->i++;
	if (stock->tmp && stock->tmp[stock->i] == '\n')
		stock->nl = 1;
	lst_new_add(&stock->start, &stock->last, stock->tmp);
	stock->size += stock->i;
	if (stock->nl || (stock->r > -1 && stock->r < BUFFER_SIZE && stock->size))
	{
		stock->line = malloc(stock->size + 2);
		if (!stock->line)
			return (clear_lst(stock->start));
		while (stock->last->content[stock->i]
			&& stock->last->content[stock->i + 1 + stock->c])
			stock->c++;
		*buf = malloc(stock->c + 1);
		if (!*buf)
			return ;
		return (cpy_lst(&stock->line, buf, *stock), clear_lst(stock->start));
	}
}

char	*get_next_line(int fd)
{
	static char	*buf[1024];
	t_stock		stock;

	stock.tmp = buf[fd];
	buf[fd] = NULL;
	stock.size = 0;
	stock.r = -2;
	stock.start = NULL;
	stock.line = NULL;
	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		ft_init_strs(&buf[fd], &stock);
		if (buf[fd] || stock.nl || (stock.r > -1 && stock.r < BUFFER_SIZE))
			return (stock.line);
		stock.tmp = malloc(BUFFER_SIZE + 1);
		if (!stock.tmp)
			return (free(stock.line), clear_lst(stock.start), NULL);
		stock.r = read(fd, stock.tmp, BUFFER_SIZE);
		if (stock.r == -1 || (stock.r == 0 && !stock.size))
			return (clear_lst(stock.start), free(stock.tmp), stock.line);
		stock.tmp[stock.r] = 0;
	}
	return (NULL);
}

//int main()
//{
//	int	i;
//	char *line;
//	i = 1;
//	while(i)
//	{
//		line = get_next_line(0);
//		if (!line)
//			i = 0;
//		printf("%s", line);
//	}
//}
