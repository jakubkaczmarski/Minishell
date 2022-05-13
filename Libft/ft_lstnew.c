/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:54:48 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/13 11:57:49 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*lst;

	lst = (t_list *) malloc(sizeof(*content));
	if (lst == NULL)
		return (NULL);
	lst->content = content;
	lst->index = 0;
	lst->next = NULL;
	return (lst);
}
