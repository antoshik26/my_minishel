/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmadelei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:36:53 by dmadelei          #+#    #+#             */
/*   Updated: 2020/11/05 23:35:29 by dmadelei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buf;
	size_t	i;

	i = 0;
	buf = malloc(count * size);
	if (buf == NULL)
		return (NULL);
	else
	{
		ft_bzero(buf, (size * count));
		return (buf);
	}
}
