/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmadelei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:04:26 by dmadelei          #+#    #+#             */
/*   Updated: 2020/11/03 19:51:15 by dmadelei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	size_t			i;
	const char		*b;

	b = arr;
	i = 0;
	if (arr)
	{
		while (i < n)
		{
			if (*b == c)
			{
				return ((void *)arr);
			}
			else
			{
				b++;
				arr++;
				i++;
			}
		}
	}
	return (NULL);
}
