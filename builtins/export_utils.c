/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:07:25 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/12 15:03:49 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
sorts or prints out the envv list in alphabetical order
*/
// void sort_list(t_list *envv)
// {
// 	//initialize index == 0
// 	t_search *curr;
// 	t_list *smallest;
// 	t_list *tmp;
	
// 	curr = envv;
// 	smallest = envv;
// 	while (curr->next != NULL)
// 	{
// 		while (curr->next != NULL)
// 		{
// 			if (ft_strncmp(curr->content, curr->next->content, \
// 				ft_strint(curr->content, '\0')))
// 			{
// 				curr->index = 1;
// 				smallest = curr->content;			
// 			}
// 			curr = curr->next;
// 		}
// 		curr = envv;
// 	}
// }