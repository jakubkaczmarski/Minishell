/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:08:39 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/24 00:00:27 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int parse(t_data *info, char *line)
{
    int i;
    i = 0;
    info->amount_cmd = 0;
    //Get rid of additional spaces if the spaces are not in the quotes
    while(line[i])
    {   
    }
}