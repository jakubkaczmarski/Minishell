/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:07:31 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/27 17:02:07 by jkaczmar         ###   ########.fr       */
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
		else if(!ft_strncmp(info->cmd_table[y], "cd", 2))
		{
			printf("CD detected\n");
			cd(info);
		}else if(!ft_strncmp(info->cmd_table[y], "pwd", 3))
		{
			printf("PWD detected\n");
			// pwd()
		}else if(!ft_strncmp(info->cmd_table[y], "exit",4))
		{
			printf("Exit detected");
		}else if(!ft_strncmp(info->cmd_table[y], "export", 6))
		{
			printf("Export detected");
		}else if(!ft_strncmp(info->cmd_table[y], "export", 6))
		{
			printf("Export detected");
		}
		y++;
	}
}