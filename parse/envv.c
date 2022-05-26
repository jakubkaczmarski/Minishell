/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:08:41 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/24 13:04:45 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
handles the input given by the user and puts it into a struct
*/
int	copy_envv(t_list **l_envv, char **envv)
{
	t_list	*s;
	t_list	*tmp;
	int		i;

	i = 0;
	if (envv)
	{
		s = ft_lstnew(envv[0]);
		while (envv[i])
		{
			tmp = ft_lstnew(envv[i]);
			ft_lstadd_back(&s, tmp);
			i++;
		}
		*l_envv = s;
		tmp = (*l_envv)->next;
		(*l_envv)->next = (*l_envv)->next->next;
		free(tmp);
		return (0);
	}
	
	return (1);
}
