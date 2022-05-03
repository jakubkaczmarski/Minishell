/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:07:31 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/03 18:25:43 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_echo(t_data *info, int counter)
{
	int i = 1;
	if(!ft_strncmp(info->formated_cmds[counter][i], "-n", 2))
	{
		i = 2;
		while(info->formated_cmds[counter][i])
		{
			printf("%s", info->formated_cmds[counter][i]);
			printf(" ");
			i++;
		}
	}else{
		i = 1;
		while(info->formated_cmds[counter][i])
		{
			printf("%s", info->formated_cmds[counter][i]);
			printf(" ");
			i++;
		}
		printf("\n");
	}
	
}