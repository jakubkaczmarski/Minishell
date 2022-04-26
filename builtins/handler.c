/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@students.42wolfsburg.de>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:07:31 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/22 15:37:34 by jtomala          ###   ########.fr       */
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

	y = 0;
	while (info->cmd_table[y])
	{
		//printf("%s\n", info->cmd_table[y]);
		if (!ft_strncmp(info->cmd_table[y], "echo", 4))
		{
			printf("'echo' detected\n");
		}
		y++;
	}
}