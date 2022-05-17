/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:54:48 by jtomala           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/16 17:08:21 by jtomala          ###   ########.fr       */
=======
/*   Updated: 2022/05/17 17:07:00 by jtomala          ###   ########.fr       */
>>>>>>> jorit
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*lst;

	lst = (t_list *) malloc(sizeof(*content));
	if (!lst)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}
