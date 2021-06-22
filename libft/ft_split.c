/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmadelei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:04:51 by dmadelei          #+#    #+#             */
/*   Updated: 2020/12/18 17:04:57 by dmadelei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		wordnum(char const *s, char c)
{
	int word;
	int cnt;

	word = 0;
	cnt = 0;
	while (s[cnt] != '\0')
	{
		if (s[cnt] != c && (s[cnt + 1] == c || s[cnt + 1] == '\0'))
			word++;
		cnt++;
	}
	return (word);
}

static int		wordlen(char const *s, char c)
{
	int cnt;
	int len;

	cnt = 0;
	len = 0;
	while (s[cnt] != c && s[cnt] != '\0')
	{
		cnt++;
		len++;
	}
	return (len);
}

static void		*free_mem(char **result)
{
	int cnt;

	cnt = 0;
	while (result[cnt])
	{
		free(result[cnt]);
		cnt++;
	}
	free(result);
	return (NULL);
}

static char		**write_in(char const *s, int word, char c, char **result)
{
	int dim1;
	int dim2;
	int len;

	dim1 = 0;
	while (dim1 < word)
	{
		while (*s == c && *s != '\0')
			s++;
		len = wordlen(s, c);
		result[dim1] = (char*)malloc(sizeof(char) * (len + 1));
		if (result[dim1] == NULL)
			return (free_mem(result));
		dim2 = 0;
		while (dim2 < len)
			result[dim1][dim2++] = *s++;
		result[dim1][dim2] = '\0';
		dim1++;
	}
	result[dim1] = NULL;
	return (result);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	int		word;

	if (!s)
		return (NULL);
	word = wordnum(s, c);
	if (!(result = (char**)malloc(sizeof(char*) * (word + 1))))
		return (NULL);
	result = write_in(s, word, c, result);
	return (result);
}
