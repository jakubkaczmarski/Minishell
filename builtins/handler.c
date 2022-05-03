/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:07:31 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/03 18:19:57 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
handles all the builtins. Goes through the command table
and if he found a command he calls the right function
*/
void builtin_handler(t_data *info, int counter)
{
	while (info->formated_cmds[counter])
	{
		//printf("%s\n", info->cmd_table[y]);
		if (!ft_strncmp(info->cmd_table[counter], "echo", 4))
		{
			ft_echo(info, counter);
		}else if(!ft_strncmp(info->cmd_table[counter], "pwd", 3))
		{
			pwd();
		}else if(!ft_strncmp(info->cmd_table[counter], "cd", 2))
		{
			cd(info, counter);
		}
		counter++;
	}
}