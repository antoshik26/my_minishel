/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmadelei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:30:57 by dmadelei          #+#    #+#             */
/*   Updated: 2020/10/31 17:16:14 by dmadelei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	size_t	i;
	char	*buf;

	buf = destination;
	i = 0;
	while (i != n)
	{
		*buf = c;
		buf++;
		i++;
	}
	return (destination);
}
