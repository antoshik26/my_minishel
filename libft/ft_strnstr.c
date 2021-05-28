/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmadelei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:45:47 by dmadelei          #+#    #+#             */
/*   Updated: 2020/11/05 23:12:39 by dmadelei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_sravnenie(size_t i, const char *haystack,
						const char *needle, size_t len)
{
	size_t	j;

	j = 0;
	while ((needle[j] == haystack[i]) & (i != len))
	{
		i = i + 1;
		j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i - j]);
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_haystack;
	size_t	i;
	char	*b;

	i = 0;
	len_haystack = ft_strlen(haystack);
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	if (len_haystack < len)
		while (haystack[i] != '\0' & i < len_haystack)
		{
			if (needle[0] == haystack[i])
				if ((b = ft_sravnenie(i, haystack, needle, len)) != NULL)
					return (b);
			i++;
		}
	else
		while (i < len)
		{
			if (needle[0] == haystack[i])
				if ((b = ft_sravnenie(i, haystack, needle, len)) != NULL)
					return (b);
			i++;
		}
	return (NULL);
}
