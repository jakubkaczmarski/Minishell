/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:07:31 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/22 13:28:21 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
handles all the builtins. Goes through the command table
and if he found a command he calls the right function
*/
void builtin_handler(t_data *info)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (info->cmd_table[y])
	{
		//printf("%s\n", info->cmd_table[y]);
		if (ft_strncmp(info->cmd_table[y], "echo", 4))
		{
			printf("target\n");
		}
		y++;
	}
}