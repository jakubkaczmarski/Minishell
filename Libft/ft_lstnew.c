/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:54:48 by jtomala           #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2022/05/16 17:08:21 by jtomala          ###   ########.fr       */
=======
/*   Updated: 2022/05/17 17:07:00 by jtomala          ###   ########.fr       */
>>>>>>> jorit
=======
/*   Updated: 2022/05/17 19:24:36 by jtomala          ###   ########.fr       */
>>>>>>> jorit
=======
/*   Updated: 2022/05/17 18:25:08 by jkaczmar         ###   ########.fr       */
>>>>>>> 39d4b09b2fcbda014c5e3088c978c70948a23fbb
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*lst;

	lst = (t_list *) malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->content = content;
	lst->index = 0;
	lst->next = NULL;
	return (lst);
}
