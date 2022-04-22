/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@students.42wolfsburg.de>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:57:02 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/22 16:08:22 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *cut_off_douq(char *input)
{
    int i;
    int index;
    char *new_input;
    
    i = 1;
    index = 0;
    new_input = ft_calloc(sizeof(char *), ft_strlen(input) - 2);
    printf("double qoute detected\n");
    while (input[i] != 34)
        i++;
    printf("i: %d\ninput+1: %s\n", i, input + 1);
    index = ft_copy(new_input, input + 1, i);
    ft_copy(&new_input[index], &input[i + 1], 0);
    //free(input);
    return (new_input);

}