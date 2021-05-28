/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memccpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmadelei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:37:45 by dmadelei          #+#    #+#             */
/*   Updated: 2020/11/12 17:57:35 by dmadelei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*dest;
	unsigned const char	*sour;

	i = 0;
	dest = (unsigned char *)dst;
	sour = (unsigned char *)src;
	if (!dst && !src)
		return (dst);
	while (n--)
	{
		if (sour[i] != (unsigned char)c)
		{
			dest[i] = sour[i];
		}
		else
		{
			dest[i] = sour[i];
			return (&dst[i + 1]);
		}
		i++;
	}
	return (NULL);
}
