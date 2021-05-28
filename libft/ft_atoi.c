/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmadelei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:08:51 by dmadelei          #+#    #+#             */
/*   Updated: 2020/11/14 22:45:00 by dmadelei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		chek_znak(const char str, size_t *i)
{
	size_t	key;



	key = 0;
	if (str == '+' || str == '-')
	{
		*i = *i + 1;
		if (str == '-')
			key = 1;
	}
	return (key);
}

int		ft_atoi(const char *str)
{
	size_t				i;
	size_t				key;
	unsigned long long	result;

	key = 0;
	i = 0;
	result = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n') ||
			(str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	key = chek_znak(str[i], &i);
	while (str[i] >= '0' & str[i] <= '9')
	{
		if (i > 19 && key == 1)
			return (0);
		if (i > 19)
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (key == 1)
		return (result * -1);
	else
		return (result);
}
