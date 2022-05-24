/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:56:45 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/24 15:42:00 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//CD 
//first check if there is an argument to the cd command
//If there isn't find HOME variable and cd into it
void	cd(t_data *info)
{
	if(!info->cmd[info->index].cmd[0])
		return ;
	char arr[4000];
	
	if(info->cmd[info->index].cmd[1])
	{
		chdir(info->cmd[info->index].cmd[1]);
		printf("%s\n", getcwd(arr, 4000));
	}else
	{
		chdir(info->path);
		printf("%s\n", getcwd(arr, 4000));
	}
}