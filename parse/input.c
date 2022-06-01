/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:11:12 by jtomala           #+#    #+#             */
/*   Updated: 2022/06/01 09:08:35 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_dollar(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && flag_check(input, i))
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
	value = return_envv_val(envv, var + 1);
	if (value)
	{
		input = modify_input(input, value, var_len);
		free(value);
	}
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
	int	i;
	int	amount;

	i = 0;
	amount = 0;
	while (input[i])
	{
		if (input[i] == '$' && flag_check(input, i))
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

	if (envv)
	{
	}
	free(info->env[0]);
	info->env[0] = ft_strdup(envv[0]);
	amount_dollars = count_dollars(input);
	while (amount_dollars-- > 0)
	{
		input = check_input(input, info->env);
		input = quote_handler(input);
	}
	input = cmd_table_handler(info, input);
	crop_redir(info);
	handle_struct(info);
	// free(info->env[0]);
	// info->env[0] = ft_strdup(envv[0]);
	// print_cmd_table(info->cmd_table);
	return (input);
}
