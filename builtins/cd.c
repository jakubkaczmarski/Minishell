/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:56:45 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/26 23:34:24 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char *find_home(t_data *info)
{
	int index;

	index =0;
	while(info->env[index] && ft_strncmp("HOME=", info->env[index], 5) != 0)
		index++;
	if(!info->env[index])
		return NULL;
	return (info->env[index]  + 5);
}
//CD 
//first check if there is an argument to the cd command
//If there isn't find HOME variable and cd into it
void	cd(t_data *info)
{
	// char *full_path;
	char *home; 
	if(!info->cmd[info->index].cmd[0])
		return ;
	char arr[4000];
	int ret;
	home = find_home(info);
	if(info->cmd[info->index].cmd[1])
	{
		ret = chdir(info->cmd[info->index].cmd[1]);
		if(ret != 0)
		{
			perror("Path name doesn't exist\n");
		}
		printf("%s\n", getcwd(arr, 4000));
	}else
	{
		printf("Path %s\n",home);
		// print_2d_array(info->env, 1);
		chdir(home);
		printf("%s\n", getcwd(arr, 4000));
	}
}