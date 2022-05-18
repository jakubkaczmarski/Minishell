/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:56:45 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/18 16:59:06 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//CD 
//first check if there is an argument to the cd command
//If there isn't find HOME variable and cd into it
void	cd(t_data *info)
{
	if(!info->command_and_param[1])
		return ;
	char arr[4000];
	
	if(info->command_and_param[1])
	{
		chdir(info->command_and_param[1]);
		printf("%s\n", getcwd(arr, 4000));
	}else
	{
		chdir(info->path);
		printf("%s\n", getcwd(arr, 4000));
	}
}