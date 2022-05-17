/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:08:41 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/17 19:37:20 by jtomala          ###   ########.fr       */
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

	i = 1;
	if (envv)
	{
		// (*l_envv)->content = envv[0];
		// (*l_envv)->next = NULL;
		// (*l_envv)->index = 0;
		s = ft_lstnew(envv[0]);
		while (envv[i])
		{
			tmp = ft_lstnew(envv[i]);
			ft_lstadd_back(&s, tmp);
			i++;
		}
		*l_envv = s;
		return (0);
	}
	return (1);
}
