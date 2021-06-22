/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmadelei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:40:24 by dmadelei          #+#    #+#             */
/*   Updated: 2021/06/22 21:11:37 by lbones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static char	*ostatok;
	char		*result;
	int			key;

	key = 0;
	if (cheak_file_descriptor_and_buf(BUFFER_SIZE, fd) == 0)
		return (-1);
	if (ostatok == NULL)
		if ((ostatok = create_buf(BUFFER_SIZE)) == NULL)
			return (-1);
	if ((result = read_in_buffer(fd, BUFFER_SIZE, &ostatok, &key)) != NULL)
	{
		if (key != 0)
		{
			*line = result;
			free(ostatok);
			ostatok = NULL;
			return (0);
		}
		*line = result;
		return (1);
	}
	return (-1);
}

int		cheak_file_descriptor_and_buf(long len_buf, int fd)
{
	if (len_buf == 0 || len_buf < 0)
		return (0);
	if (fd > 100 || fd < 0)
		return (0);
	return (1);
}

char	*create_buf(long len_buf)
{
	char	*buf;
	int		i;

	i = 0;
	buf = (char *)malloc(sizeof(char) * (len_buf + 1));
	if (buf == NULL)
		return (NULL);
	while (i < len_buf)
	{
		buf[i] = '\0';
		i++;
	}
	return (buf);
}
