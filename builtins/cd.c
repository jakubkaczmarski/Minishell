/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:56:45 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/05 19:38:17 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_home(t_data *info)
{
	int	index;

	index = 0;
	while (info->env[index] && ft_strncmp("HOME=", info->env[index], 5) != 0)
		index++;
	if (!info->env[index])
		return (NULL);
	return (info->env[index] + 5);
}
// CD
// first check if there is an argument to the cd command
// If there isn't find HOME variable and cd into it

void	cd(t_data *info)
{
	char	*home;
	int		ret;

	if (!info->cmd[info->index].cmd[0])
		return ;
	home = find_home(info);
	if (info->cmd[info->index].cmd[1])
	{
		ret = chdir(info->cmd[info->index].cmd[1]);
		if (ret != 0)
		{
			perror("Path name doesn't exist\n");
		}
	}
	else
	{
		chdir(home);
	}
}
