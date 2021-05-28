/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmadelei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:47:43 by dmadelei          #+#    #+#             */
/*   Updated: 2020/11/07 12:37:25 by dmadelei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		create_buf(char **buf, int n, size_t i)
{
	if (n <= 0)
	{
		*buf = (char *)malloc(sizeof(char) * i + 2);
		if (*buf == NULL)
			return (0);
	}
	else
	{
		*buf = (char *)malloc(sizeof(char) * i + 1);
		if (*buf == NULL)
			return (0);
	}
	return (1);
}

void	chek_znak_2(unsigned int *copy,
					unsigned int *copy_2, size_t *znak, int n)
{
	if (n < 0)
	{
		*znak = 1;
		*copy = n * -1;
		*copy_2 = n * -1;
	}
	else
	{
		*znak = 0;
		*copy = n;
		*copy_2 = n;
	}
}

void	len_int(unsigned int *copy, size_t *i)
{
	*i = 0;
	while (*copy > 0)
	{
		*copy = *copy / 10;
		*i = *i + 1;
	}
}

void	completion_buf(unsigned int copy_2, size_t i, char *buf)
{
	while (copy_2 > 0)
	{
		buf[i] = (copy_2 % 10) + '0';
		copy_2 = copy_2 / 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	unsigned int	copy;
	unsigned int	copy_2;
	size_t			i;
	char			*buf;
	size_t			znak;

	chek_znak_2(&copy, &copy_2, &znak, n);
	len_int(&copy, &i);
	if (create_buf(&buf, n, i) == 0)
		return (NULL);
	if (n == 0)
	{
		buf[i + 1] = '\0';
		buf[i] = '0';
		return (buf);
	}
	if (znak == 1)
	{
		buf[0] = '-';
		i++;
	}
	buf[i] = '\0';
	i--;
	completion_buf(copy_2, i, buf);
	return (buf);
}
