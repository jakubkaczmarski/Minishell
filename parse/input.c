/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:11:12 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/27 10:08:25 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_dollar(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && ((input[i - 1] != '\'') \
			|| (input[i - 1] == '\'' && input[i - 2] == '"')))
			return (&input[i]);
		i++;
	}
	return (NULL);
}

/*
is checking the input for $-sign and replaces the variable by the value
*/
char	*check_input(char *input, char **envv)
{
	char	*var;
	char	*value;
	char	*pos_dollar;
	int		var_len;

	pos_dollar = find_dollar(input);
	var = get_value(pos_dollar, &var_len);
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
counts how many dollar signgs are in the input so 
he function in the handler know how many variables
have to get replaced.
*/
int	count_dollars(char *input)
{
	int		i;
	int		amount;

	i = 0;
	amount = 0;
	while (input[i])
	{
		if (input[i] == '$' && ((input[i - 1] != '\'') \
			|| (input[i - 1] == '\'' && input[i - 2] == '"')))
			amount++;
		i++;
	}
	return (amount);
}

/*
put envv in a struct and replace them with the actual values
*/
char	*handle_input(t_data *info, char *input, char **envv)
{
	int	amount_dollars;

	amount_dollars = count_dollars(input);
	while (amount_dollars-- > 0)
		input = check_input(input, envv);
	input = quote_handler(input);
	cmd_table_handler(info, input);
	//printf("[%d]%s\n", counter, info->cmd_table[counter]);
	return (input);
}
