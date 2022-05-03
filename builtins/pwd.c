/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:22:13 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/03 15:24:32 by jkaczmar         ###   ########.fr       */
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
    // free(str);
}
