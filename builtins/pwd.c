/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:52:56 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/18 16:56:01 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_path(void)
{
	char buff[4096];
    char *str;
	
	str = getcwd(&buff[0], sizeof(buff));
    if(!str)
        return ;
    printf("%s\n", str);
}