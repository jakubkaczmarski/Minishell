/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@students.42wolfsburg.de>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 08:09:29 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/26 08:19:25 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_cmd_table(char **cmd_table)
{
    int i = 0;
    while (cmd_table[i])
    {
        printf("[%d] %s\n", i, cmd_table[i]);
        i++;
    }
}

void cmd_table_handler(t_data *info, char *input)
{
    //int counter;

    //counter = 0;
    //info->cmd_table[counter] = ft_calloc(sizeof(char *), ft_strlen(input) + 1);
	//ft_copy(info->cmd_table[counter], input, 0);
    info->cmd_table = ft_split(input, '|');
    print_cmd_table(info->cmd_table);
}