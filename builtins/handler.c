/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:07:31 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/29 19:46:12 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_echo_and_env(t_data *info)
{
	if (!ft_strncmp(info->cmd[info->index].cmd[0], "echo", 4))
	{
		ft_echo(info);
		info->ret_val = 0;
		return (1);
	}
	else if (!ft_strncmp(info->cmd[info->index].cmd[0], "$?", 2))
	{
		printf(" %d ", info->ret_val);
		info->ret_val = 127;
		return (1);
	}
	return (0);
}

/*
handles all the builtins. Goes through the command table
and if he found a command he calls the right function
*/
int	builtin_handler(t_data *info)
{
	if (info->cmd[info->index].cmd[0])
	{
		if (check_echo_and_env(info) == 1)
		{
		}
		else if (!ft_strncmp(info->cmd[info->index].cmd[0], "env", 3))
		{
			print_2d_array(info->env, 1);
			info->ret_val = 0;
			return (1);
		}
		else if (!ft_strncmp(info->cmd[info->index].cmd[0], "pwd", 3))
		{
			print_path();
			info->ret_val = 0;
			return (1);
		}
		else
			return (-1);
	}
	return (0);
}
