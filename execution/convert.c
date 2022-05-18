/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 13:51:37 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/18 13:57:14 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **convert(t_list *envv)
{
	char **arr;
	int i;

	arr = malloc(sizeof(char **));
	i = 0;
	while (envv != NULL)
	{
		arr[i] = malloc(sizeof(envv->content));
		ft_copy(arr[i], envv->content, ft_strlen(envv->content));
		envv = envv->next;
	}
	return (arr);
}