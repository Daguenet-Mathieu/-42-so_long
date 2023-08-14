/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:25:47 by madaguen          #+#    #+#             */
/*   Updated: 2023/01/21 01:38:14 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

typedef struct s_lst
{
	char			*content;
	struct s_lst	*next;
}					t_lst;

typedef struct s_stock
{
	char	*tmp;
	char	*line;
	int		r;
	int		nl;
	int		i;
	int		c;
	int		size;
	t_lst	*start;
	t_lst	*last;
}			t_stock;

char	*get_next_line(int fd);

#endif
