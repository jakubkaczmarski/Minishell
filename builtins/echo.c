/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:07:31 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/18 16:39:20 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_data *info)
{
	int		flag;
	int		i;

	flag = 0;
	i = 1;
	//echo -n -n-n-n-n-n bla bla bla
	if (!info->command_and_param[1])
	{
		printf("\n");
		return ;
	}
	//if str[1] == -n set flag to 1
	if (!ft_strncmp(info->command_and_param[1], "-n", 2))
	{
		flag = 1;
		i++;
	}
	if (!info->command_and_param[1] && !info->command_and_param[2])
	{
		return ;
	}
	while (info->command_and_param[i])
		printf("%s ", info->command_and_param[i++]);
	if (flag == 0)
		printf("\n");
}
