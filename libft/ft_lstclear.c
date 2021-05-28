/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmadelei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:02:42 by dmadelei          #+#    #+#             */
/*   Updated: 2020/11/10 18:01:00 by dmadelei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*a;
	t_list	*b;

	if (!lst)
		return ;
	a = *lst;
	while (a)
	{
		b = a->next;
		del(a);
		a = b;
	}
	*lst = NULL;
}
