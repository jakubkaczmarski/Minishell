/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 11:27:00 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/04/24 14:45:57 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void pwd(void)
{
    char buff[4096];
    char *str = getcwd(&buff[0], sizeof(buff));
    if(!str)
        return ;
    printf("%s\n", str);
}
