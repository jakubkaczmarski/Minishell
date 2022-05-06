/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:55:29 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/06 10:56:00 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
counts all the pipes that have a space before and/or after a pipe
*/
int	count_pipes(char *input)
{
	int	i;
	int	amount_pipes;

	i = 0;
	amount_pipes = 0;
	while (input[i])
	{
		if (input[i] == '|' && (input[i - 1] == ' ' || input[i + 1] == ' '))
			amount_pipes++;
		i++;
	}
	return (amount_pipes);
}

/*
counts how many multi spaces are in the string
*/
int	count_multis(char *input)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ' && input[i + 1] == ' ')
		{
			while (input[i] == ' ')
				i++;
			counter++;
		}
		i++;
	}
	return (counter);
}
