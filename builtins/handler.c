/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:07:31 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/18 00:47:34 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
handles all the builtins. Goes through the command table
and if he found a command he calls the right function
*/
int	builtin_handler(t_data *info)
{
	int	y;

	y = 0;
	while (info->cmd_table[y])
	{
		if (!ft_strncmp(info->cmd_table[y], "echo", 4))
		{
			ft_echo(info->cmd_table[y]);
			return 1;
		}
		else if (!ft_strncmp(info->cmd_table[y], "export", 6))
		{
			export_handler(info, y);
			return 1;
		}
		else if (!ft_strncmp(info->cmd_table[y], "unset", 5))
		{
			unset_handler(info, y);
			return 1;
		}
		else if (!ft_strncmp(info->cmd_table[y], "env", 3))
		{
			print_envv(info->envv, 0);
			return 1;
		}
		else
		{
			printf("No build ins found\n");
			return -1;
		}
		y++;
	}
	return 0;
}
