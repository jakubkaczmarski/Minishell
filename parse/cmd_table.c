/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 08:09:29 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/28 10:52:56 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **remove_spaces(char **cmd_table)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (cmd_table[y])
    {
        while (cmd_table[y][x])
        {
            if (cmd_table[y][x] == '|')
            {
                //remove the char (x - 1) and (x + 1):
                //  copy (x - 1) character in a new string
                //  copy the pipe into the string
                //  copy at (x + 1) until the rest -> 0
            }
            x++;
        }
        x = 0;
        y++;
    }
    return (cmd_table);
}

/*
[testfunction] prints out the command table
*/
void print_cmd_table(char **cmd_table)
{
    int i;

    i = 0;
    while (cmd_table[i])
    {
        printf("[%d] %s\n", i, cmd_table[i]);
        i++;
    }
}

/*
takes the input in puts it into the cmd_table. 
before that, it removes the spaces around the pipe
and then splits the input by pipe.
*/
void cmd_table_handler(t_data *info, char *input)
{
    info->cmd_table = ft_split(input, '|');
    info->cmd_table = remove_spaces(info->cmd_table);
    print_cmd_table(info->cmd_table);
}