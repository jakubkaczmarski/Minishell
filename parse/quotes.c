/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:57:02 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/18 08:34:20 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
@param 34 double quote
@param 39 single quote

counts how many dollar signs are in the input 
but keeps track on the quoations
*/
char	*quote_handler(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == 34)
			input = cut_off_douq(input);
		i++;
	}
	return (input);
}

/*
cuts off the double quotes
*/
char	*cut_off_douq(char *input)
{
	int		i;
	int		j;
	int		index;
	char	*new_input;

	i = 1;
	j = 1;
	index = 0;
	new_input = ft_calloc(sizeof(char *), ft_strlen(input) - 2);
	while (input[i] != 34)
		i++;
	index = ft_copy(new_input, input, i + 1);
	while (input[i + j] != 34)
		j++;
	index += ft_copy(&new_input[index], &input[i + 1], j);
	ft_copy(&new_input[index], &input[index + 2], 0);
	free(input);
	return (new_input);
}
