/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@students.42wolfsburg.de>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:11:12 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/22 16:05:26 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
is checking the input for $-sign and replaces the variable by the value
*/
char	*check_input(char *input, char **envv)
{
	char	*var;
	char	*value;
	int		var_len;

	var = get_value(ft_strchr(input, '$'), &var_len);
	if (var)
	{
		value = return_envv_val(envv, var + 1);
		input = modify_input(input, value, var_len);
	}
	if (var)
		free(var);
	return (input);
}

/*
@param 34 double quote
@param 39 single quote

counts how many dollar signs are in the input 
but keeps track on the quoations
*/
int count_dollars(char *input)
{
	int i;
	int amount_dollars;

	i = 0;
	amount_dollars = 0;
	while (input[i])
	{
		//printf("%c => %d\n", input[i], (int) input[i]);
		if ((int) input[i] == 39 && input[i - 1] == 34) //first double then single quote
			input = cut_off_douq(&input[i - 1]);
		if (input[i] == '$')
			amount_dollars++;
		i++;
	}
	printf("NEW_INPUT: %s\n", input);
	return (amount_dollars);
}

/*
put envv in a struct and replace them with the actual values
*/
char	*handle_input(t_data *info, char *input, int counter, char **envv)
{
	//int	i;
	int	amount_dollars;

	//i = 0;
	amount_dollars = count_dollars(input);
	//while (input[i])
	//	if (input[i++] == '$')
	//		amount_dollars++;
	while (amount_dollars-- > 0)
		input = check_input(input, envv);
	info->cmd_table[counter] = ft_calloc(sizeof(char *), ft_strlen(input) + 1);
	ft_copy(info->cmd_table[counter], input, 0);
	printf("[%d]%s\n", counter, info->cmd_table[counter]);
	return (input);
}
