/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 00:35:13 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/04 17:05:05 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_only_nums(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '+' && str[i + 1]) || (str[i] == '-' && str[i + 1]))
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (-1);
		}
		i++;
	}
	return (1);
}

void	exit_program(t_data *info)
{
	int	i;

	i = 0;
	// free_2d_array(info->env);
	// free(info->cmd_table[0]);
	// free(info->envv);
	if (!info->cmd[info->index].cmd[i + 1])
	{
		exit(0);
	}
	else if (info->cmd[info->index].cmd[i + 2])
	{
		perror("Too many arguments\n");
		return ;
	}
	if (info->cmd[info->index].cmd[i + 1])
	{
		if (check_if_only_nums(info->cmd[info->index].cmd[i + 1]) == 1)
		{
			exit(ft_atoi((const char *)info->cmd[info->index].cmd[i + 1]));
		}
		else
		{
			perror("Non numerical arguments");
			exit(1);
		}	
	}
}
