/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmadelei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:02:30 by dmadelei          #+#    #+#             */
/*   Updated: 2020/11/12 18:00:10 by dmadelei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	char			*dest;
	const char		*sour;

	i = 0;
	dest = dst;
	sour = src;
	if ((dst) || (src))
	{
		while (i != n)
		{
			*dest++ = *sour++;
			i++;
		}
	}
	return (dst);
}
