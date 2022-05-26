/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:07:31 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/26 17:16:01 by jkaczmar         ###   ########.fr       */
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
	if(info->cmd[info->index].cmd[0])
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
		else if (!ft_strncmp(info->cmd[info->index].cmd[0], "env", 3))
		{
			print_envv(info->envv, 0);
			info->ret_val = 0;
			return (1);
		}else if (!ft_strncmp(info->cmd[info->index].cmd[0], "pwd", 3))
		{
			print_path();
			info->ret_val = 0;
			return (1);
		}
		else
			return (-1);
		y++;
	}
	return (0);
}

void exit_program(t_data *info)
{
	int i;

	i = 0;
	if(!info->cmd[info->index].cmd[i + 1])
	{
		exit(0);
	}
	// while(info->cmd[info->index].cmd[i])
	// {
		// if()
		// i++;
	// }
}