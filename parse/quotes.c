/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:57:02 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/25 12:09:30 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
should cut of the double quotes so I tested it with:
    "'$USER'" -> '$USER' 
*/
char *cut_off_douq(char *input)
{
    int i;
    int j;
    int index;
    char *new_input;
    
    i = 1;
    j = 1;
    index = 0;
    new_input = ft_calloc(sizeof(char *), ft_strlen(input) - 2);
    while (input[i] != 34)
        i++;
    index = ft_copy(new_input, input, i + 1); //copy up to the first
    while (input[i + j] != 34)
        j++;
    index += ft_copy(&new_input[index], &input[i + 1], j); //copy until the second "
    ft_copy(&new_input[index], &input[index + 2], 0);                  //copy after the secound "
    free(input);
    return (new_input);

}