/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:07:05 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/04/27 16:50:35 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//CD 
//first check if there is an argument to the cd command
//If there isn't find HOME variable and cd into it
void	cd(t_data *info)
{
	if(!info->cmd)
		return ;
	char arr[4000];
	char *home_thingy;
	
	if(info->cmd_table[1])
	{
		chdir(info->cmd_table[1]);
		printf("%s\n", getcwd(arr, 4000));
	}else
	{
		while(info->envv->next)
		{
			if(strncmp(info->envv->content, "HOME=", 5) == 0)
			{
				printf("%s\n", info->envv->content);
				home_thingy = info->envv->content;
			}
			info->envv = info->envv->next;
		}
		chdir(&home_thingy[5]);
		printf("%s\n", getcwd(arr, 4000));
	}
}