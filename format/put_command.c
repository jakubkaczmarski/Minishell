/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:51:37 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/03 15:20:44 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Take the command split it by spaces and put it into three dimensianal array
//0 index will be a command itself
//Rest of the indexes will be arguments

void format_line(t_data *info, int counter)
{
    info->formated_cmds[counter] = ft_split(info->cmd_table[counter], ' ');
}

void print_lines(t_data *info, int counter)
{
	while(counter != 0)
	{
		int j = 0;
		printf("Line :\n");
		counter--;
		while(info->formated_cmds[counter][j])
		{
			printf("%s \t", info->formated_cmds[counter][j]);
			free(info->formated_cmds[counter][j]);
			j++;
		}
		printf("\n");
		free(info->formated_cmds[counter]);
	}
}


void    delete_env_list(t_data *info)
{
    if(!info)
    {};
    // while(info->envv->next != NULL)
    // {
    //     free(info->envv);
    // }
}
// void put_cmd(t_data info)
// {
    
//     // while(cmd)
// }
