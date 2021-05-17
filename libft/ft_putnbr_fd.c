/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmadelei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:29:46 by dmadelei          #+#    #+#             */
/*   Updated: 2020/11/12 19:29:04 by dmadelei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		len_int(unsigned int *copy, size_t *znak, int n)
{
	size_t	len_n;

	len_n = 0;
	if (n < 0)
	{
		*copy = n * -1;
		*znak = 1;
		while (*copy > 0)
		{
			len_n++;
			*copy = *copy / 10;
		}
		*copy = n * -1;
	}
	else
	{
		*copy = n;
		while (*copy > 0)
		{
			len_n++;
			*copy = *copy / 10;
		}
		*copy = n;
	}
	return (len_n);
}

void			psevdo_mass(int len_n, unsigned int copy, int fd)
{
	char	mass[len_n + 1];
	int		i;

	i = 0;
	while (i < len_n)
	{
		mass[i] = (copy % 10) + '0';
		copy = copy / 10;
		i++;
	}
	len_n = len_n - 1;
	while (len_n != -1)
	{
		write(fd, &mass[len_n], 1);
		len_n--;
	}
}

void			ft_putnbr_fd(int n, int fd)
{
	unsigned int	copy;
	int				len_n;
	size_t			znak;

	znak = 0;
	len_n = 0;
	if (n == 0)
		write(fd, "0", 1);
	len_n = len_int(&copy, &znak, n);
	if (znak == 1)
		write(fd, "-", 1);
	psevdo_mass(len_n, copy, fd);
}
