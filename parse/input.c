/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:11:12 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/22 13:59:55 by jtomala          ###   ########.fr       */
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
put envv in a struct and replace them with the actual values
*/
char	*handle_input(t_data *info, char *input, int counter, char **envv)
{
	int	i;
	int	amount_dollars;

	i = 0;
	amount_dollars = 0;
	while (input[i])
		if (input[i++] == '$')
			amount_dollars++;
	while (amount_dollars-- > 0)
		input = check_input(input, envv);
	info->cmd_table[counter] = ft_calloc(sizeof(char *), ft_strlen(input) + 1);
	ft_copy(info->cmd_table[counter], input, 0);
	printf("[%d]%s\n", counter, info->cmd_table[counter]);
	return (input);
}
