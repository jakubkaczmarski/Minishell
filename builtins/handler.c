/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:07:31 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/12 10:17:17 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
handles all the builtins. Goes through the command table
and if he found a command he calls the right function
*/
void	builtin_handler(t_data *info)
{
	int	y;

	y = 0;
	while (info->cmd_table[y])
	{
		if (!ft_strncmp(info->cmd_table[y], "echo", 4))
		{
			ft_echo(info->cmd_table[y]);
		}
		else if (!ft_strncmp(info->cmd_table[y], "export", 6))
			export_handler(info, y);
		else if (!ft_strncmp(info->cmd_table[y], "unset", 5))
			unset_handler(info, y);
		else if (!ft_strncmp(info->cmd_table[y], "env", 3))
			print_envv(info->envv, 0);
		else
		{
			printf("minishell> %s: command not found\n", info->cmd_table[y]);
			return ;
		}
		y++;
	}
}
