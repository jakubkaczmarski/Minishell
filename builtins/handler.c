/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:07:31 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/19 09:12:42 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void dollar_questionmark(t_data *info)
// {
// 	char *s;

// 	perror("send help\n");
// 	s = ft_strjoin("command not found:", ft_itoa(info->ret_val));
// 	perror(s);
// }

/*
handles all the builtins. Goes through the command table
and if he found a command he calls the right function
*/
int	builtin_handler(t_data *info)
{
	int	y;

	y = 0;
	if(info->command_and_param)
	{
		if (!ft_strncmp(info->command_and_param[y], "echo", 4))
		{
			ft_echo(info);
			info->ret_val = 0;
			return (1);
		}
		else if (!ft_strncmp(info->command_and_param[y], "$?", 2))
		{
			//dollar_questionmark(info);
			
			info->ret_val = 127;
		}
		else if (!ft_strncmp(info->command_and_param[y], "export", 6))
		{
			export_handler(info, y);
			info->ret_val = 0;
			return (1);
		}
		else if (!ft_strncmp(info->command_and_param[y], "unset", 5))
		{
			unset_handler(info, y);
			info->ret_val = 0;
			return (1);
		}
		else if (!ft_strncmp(info->command_and_param[y], "env", 3))
		{
			print_envv(info->envv, 0);
			info->ret_val = 0;
			return (1);
		}else if (!ft_strncmp(info->command_and_param[y], "pwd", 3))
		{
			print_path();
			info->ret_val = 0;
			return (1);
		}else if (!ft_strncmp(info->command_and_param[y], "cd", 2))
		{
			cd(info);
			info->ret_val = 0;
			return (1);
		}
		else
			return (-1);
		y++;
	}
	return (0);
}
