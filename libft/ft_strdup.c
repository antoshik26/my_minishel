/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmadelei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:41:56 by dmadelei          #+#    #+#             */
/*   Updated: 2020/11/02 14:42:42 by dmadelei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy_s1;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (s1[len] != '\0')
	{
		len++;
	}
	copy_s1 = (char *)malloc(sizeof(char) * (len + 1));
	if (copy_s1 == NULL)
		return (NULL);
	while (i < len)
	{
		copy_s1[i] = s1[i];
		i++;
	}
	copy_s1[i] = '\0';
	return (copy_s1);
}
