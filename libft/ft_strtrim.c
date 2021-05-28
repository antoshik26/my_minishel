/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmadelei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:04:17 by dmadelei          #+#    #+#             */
/*   Updated: 2020/12/18 17:04:29 by dmadelei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		cnt;
	int		fin;

	if (!s1 || !set)
		return (NULL);
	cnt = 0;
	while (ft_strchr(set, s1[cnt]) && s1[cnt])
		cnt++;
	fin = ft_strlen(s1);
	{
		while (ft_strchr(set, s1[fin]) && fin > 1)
			fin--;
	}
	result = ft_substr(s1, cnt, fin - cnt + 1);
	return (result);
}
