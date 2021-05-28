/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmadelei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:17:20 by dmadelei          #+#    #+#             */
/*   Updated: 2020/11/07 13:54:54 by dmadelei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	completion_mass(unsigned int start, size_t len,
						char *buf, const char *s)
{
	size_t	j;
	size_t	i;

	i = start;
	j = 0;
	while (i != (start + len))
	{
		buf[j] = s[i];
		i++;
		j++;
	}
	buf[j] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	size_t	i;
	char	*buf;

	i = start;
	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (len_s <= start)
	{
		buf = (char *)malloc(sizeof(char));
		buf[0] = '\0';
		return (buf);
	}
	buf = (char *)malloc(sizeof(char) * (len + 1));
	if (buf == NULL)
		return (NULL);
	completion_mass(start, len, buf, s);
	return (buf);
}
