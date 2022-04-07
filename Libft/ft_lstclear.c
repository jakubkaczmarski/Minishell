/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 09:18:54 by jtomala           #+#    #+#             */
/*   Updated: 2021/12/01 09:49:23 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem;

	elem = *lst;
	if (!del || !lst || !*lst)
		return ;
	while (lst && *lst)
	{
		elem = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = elem;
	}
}
