/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:07:31 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/28 17:41:37 by jkaczmar         ###   ########.fr       */
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
			char **arr_thingy = convert_env_list_to_str(&info->envv);
			print_2d_array(arr_thingy, 1);
			// print_envv(&(info->envv), 0);
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
int	check_if_only_nums(char *str)
{
	int i = 0;
	while(str[i])
	{
		if(str[i] < '0' || str[i] > '9')
		{
			return -1;
		}
		i++;
	}
	return 1;
}
void exit_program(t_data *info)
{
	int i;

	i = 0;
	if(!info->cmd[info->index].cmd[i + 1])
	{
		exit(0);
	}else if(info->cmd[info->index].cmd[i + 2])
	{
		perror("Too many arguments\n");
		return ;
	}
	if(info->cmd[info->index].cmd[i + 1])
	{
		if(check_if_only_nums(info->cmd[info->index].cmd[i + 1]) == 1)
		{
			exit(ft_atoi((const char *)info->cmd[info->index].cmd[i + 1]));
		}else{
			perror("Non numerical arguments");
		}
	}
}