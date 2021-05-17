/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmadelei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:40:33 by dmadelei          #+#    #+#             */
/*   Updated: 2020/12/01 18:18:37 by dmadelei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_in_buffer(int fd, long len_buf, char **ostatok, int *key)
{
	int		read_count;
	char	*p_n;
	char	*result;
	char	*tmp;
	char	buf[len_buf + 1];

	read_count = 0;
	p_n = chek_remain(*ostatok, &result);
	while (!p_n && (read_count = (read(fd, buf, len_buf))) != 0)
	{
		buf[read_count] = '\0';
		if ((p_n = ft_strchr(buf, '\n')))
		{
			*p_n = '\0';
			p_n++;
			free(*ostatok);
			*ostatok = ft_strdup(p_n);
		}
		tmp = result;
		if ((result = ft_strjoin(result, buf)) == NULL)
			return (NULL);
		free(tmp);
	}
	*key = (read_count == 0 && ft_strlen(*ostatok) == 0 && p_n == NULL) ? 1 : 0;
	return (result);
}

char	*chek_remain(char *ostatoc, char **result)
{
	char *p_n;

	p_n = NULL;
	if (ostatoc)
	{
		if ((p_n = ft_strchr(ostatoc, '\n')))
		{
			*p_n = '\0';
			*result = ft_strdup(ostatoc);
			p_n++;
			ft_strcpy(ostatoc, p_n);
		}
		else
		{
			*result = ft_strdup(ostatoc);
			while (*ostatoc)
			{
				*ostatoc = '\0';
				ostatoc++;
			}
		}
	}
	return (p_n);
}

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

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*a;

	i = 0;
	a = (char *)s;
	while (a[i] != '\0')
	{
		if (a[i] == c)
		{
			return (&a[i]);
		}
		i++;
	}
	if (c == '\0')
		return (&a[i]);
	return (NULL);
}

char	*ft_strcpy(char *dst, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
