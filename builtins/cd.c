/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:55:32 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/03 18:17:27 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


//CD 
//first check if there is an argument to the cd command
//If there isn't find HOME variable and cd into it
void	cd(t_data *info, int counter)
{
	if(!info->cmd)
		return ;
	char arr[4000];
	char *home_thingy;
	
	if(info->formated_cmds[counter][1])
	{
		chdir(info->formated_cmds[counter][1]);
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