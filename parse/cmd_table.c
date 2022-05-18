/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 08:09:29 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/18 09:39:43 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
[testfunction] prints out the command table
*/
void	print_cmd_table(char **cmd_table)
{
	int	i;

	i = 0;
	while (cmd_table[i])
	{
		printf("[%d] %s\n", i, cmd_table[i]);
		i++;
	}
}

/*
removes the spaces around a a pipe
*/
char	*remove_spaces(char *input, int x, int i)
{
	char	*new_str;

	new_str = ft_calloc(sizeof(char *), ft_strlen(input));
	if (input[x - 1] == ' ')
		i = ft_copy(new_str, input, x);
	else
		i = ft_copy(new_str, input, x + 1);
	i += ft_copy(&new_str[i], &input[x], 2);
	if (input[x + 1] == ' ')
		ft_copy(&new_str[i], &input[x + 2], 0);
	else
		ft_copy(&new_str[i], &input[x + 1], 0);
	free(input);
	return (new_str);
}

/*
checks if there are spaces around a pipe (which is not in a quote)
and removes them
*/
char	*remove_spaces_at_pipes(char *input)
{
	int		x;
	int		i;
	char	*new_str;
	int		flag;

	x = 0;
	i = 0;
	flag = 0;
	while (input[x])
	{
		if (input[x] == '\'' && flag == 0)
			flag = 1;
		else if (input[x] == '\'' && flag == 1)
			flag = 0;
		if (input[x] == '|' && (input[x - 1] == ' ' || input[x + 1] == ' ') \
			&& flag == 0)
		{
			new_str = remove_spaces(input, x, i);
			return (new_str);
		}
		x++;
	}
	return (input);
}

/*
if somewhere is more then one space in a row
remove all additional
*/
char	*remove_multi_spaces(char *input, int i, int j)
{
	int		counter;
	char	*new_input;

	counter = 0;
	new_input = ft_calloc(sizeof(char *), ft_strlen(input) + 1);
	if (!new_input)
		return (input);
	while (input[i])
	{
		if (input[i] == ' ' && input[i + 1] == ' ' && flag_check(input, i))
		{
			while (input[i + counter] == ' ')
				counter++;
			j = ft_copy(new_input, input, i + 2);
			ft_copy(&new_input[j], &input[i + counter], 0);
			i += counter;
			counter = 0;
		}
		i++;
	}
	if (j == 0)
		return (input);
	free(input);
	return (new_input);
}

/*
takes the input in puts it into the cmd_table. 
before that, it removes the spaces around the pipe
and then splits the input by pipe.
*/
char	*cmd_table_handler(t_data *info, char *input)
{
	int	amount_pipes;
	int	amount_multis;

	amount_pipes = count_pipes(input);
	amount_multis = count_multis(input);
	while (amount_pipes-- > 0)
		input = remove_spaces_at_pipes(input);
	while (amount_multis-- > 0)
		input = remove_multi_spaces(input, 0, 0);
	info->cmd_table = ft_split(input, '|');
	return (input);
}
