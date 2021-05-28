/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmadelei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:24:01 by dmadelei          #+#    #+#             */
/*   Updated: 2020/11/05 23:28:30 by dmadelei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	char	*buf;

	if (!s1)
		return (NULL);
	len_s1 = 0;
	len_s2 = 0;
	i = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	buf = (char *)malloc(sizeof(char) * (len_s1 + len_s2) + 1);
	if (buf == NULL)
		return (NULL);
	while (i < (len_s1 + len_s2))
	{
		if (i < len_s1)
			buf[i] = s1[i];
		else
			buf[i] = s2[i - len_s1];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}
