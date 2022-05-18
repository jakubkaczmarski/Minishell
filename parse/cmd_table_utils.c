/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:55:29 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/18 09:39:51 by jtomala          ###   ########.fr       */
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
		if (input[i] == ' ' && input[i + 1] == ' ' && flag_check(input, 1))
		{
			while (input[i] == ' ')
				i++;
			counter++;
		}
		i++;
	}
	return (counter);
}

/*
check if a quote is opend
*/
int	flag_check(char *input, int counter)
{
	int	i;
	int	flag_s;
	int	flag_d;

	i = 0;
	flag_d = 0;
	flag_d = 0;
	while (i <= counter)
	{
		if (input[i] == 39 && flag_s == 0)
			flag_s = 1;
		else if (input[i] == 39 && flag_s == 1)
			flag_s = 0;
		else if (input[i] == 34 && flag_d == 0)
			flag_d = 1;
		else if (input[i] == 34 && flag_d == 1)
			flag_d = 0;
		i++;
	}
	if (flag_s == 1 || flag_d == 1)
		return (0);
	return (1);
}
