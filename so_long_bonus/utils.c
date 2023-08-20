/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:26:02 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/20 16:29:52 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_putnbr(int n)
{
	unsigned int	nb;
	char			c;

	if (n < 0 && write(1, "-", 1))
		n = n * -1;
	nb = n;
	if (n >= 10)
		ft_putnbr(n / 10);
	c = nb % 10 + 48;
	write(1, &c, 1);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	ft_error(char *s)
{
	ft_putstr(s, 2);
}
