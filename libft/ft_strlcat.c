/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmadelei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:01:11 by dmadelei          #+#    #+#             */
/*   Updated: 2020/11/05 23:08:22 by dmadelei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	j = 0;
	while (dst[i] != '\0' && i < dstsize)
		i++;
	size = i;
	while (((i + 1) < dstsize) & (src[j] != '\0'))
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	if (size < i)
		dst[i] = '\0';
	return (size + ft_strlen(src));
}
