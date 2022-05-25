/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:11:12 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/25 19:05:55 by jkaczmar         ###   ########.fr       */
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

int replace_line(t_data *info, int index)
{
	int i = 0;
	int j = 0;
	char *new_line;
	new_line = ft_calloc(sizeof(char) ,ft_strlen(info->cmd_table[i]));
	
	while(info->cmd_table[index][i])
	{
		
		if(info->cmd_table[index][i] == '<')
		{
			new_line[j] = info->cmd_table[index][i];
			j++;
			if(info->cmd_table[index][i + 1] && info->cmd_table[index][i + 1] == '<' )
			{
				new_line[j] = info->cmd_table[0][i + 1];
				if(info->cmd_table[index][i + 2] && info->cmd_table[index][i + 2] == '<')
				{
					perror("INPUT ERROR");
					return -1;
				}
				i += 2;
				j++;
				while(info->cmd_table[index][i] == ' ')
				{
					i++;
				}
			}else{
				i++;
			}
		}else if(info->cmd_table[index][i] == '>')
		{
				if(info->cmd_table[index][i] == '>')
		{
			new_line[j] = info->cmd_table[index][i];
			j++;
			if(info->cmd_table[index][i + 1] && info->cmd_table[index][i + 1] == '>' )
			{
				new_line[j] = info->cmd_table[index][i + 1];
				if(info->cmd_table[index][i + 2] && info->cmd_table[index][i + 2] == '>')
				{
					perror("INPUT ERROR");
					return -1;
				}
				i += 2;
				j++;
				while(info->cmd_table[index][i] == ' ')
				{
					i++;
				}
			}else{
				i++;
			}
		}
		}
		new_line[j] = 	info->cmd_table[index][i];
		j++;
		i++;
	}
	free(info->cmd_table[index]);
	info->cmd_table[index] = new_line;
	return 0;
}
int	crop_redir(t_data *info)
{
	int	i;

	i = 0;
	while(info->cmd_table[i])
	{
		if(replace_line(info, i) == -1)
		{
			return -1;
		}
		i++;
	}
 	return 0;
}


/*
put envv in a struct and replace them with the actual values
*/
char	*handle_input(t_data *info, char *input, char **envv)
{
	int	amount_dollars;

	if (ft_strncmp(input, "exit", 4) == 0)
		return (NULL);
	if (ft_strncmp(input, "$?", 2) == 0)
		return (cmd_table_handler(info, input));
	amount_dollars = count_dollars(input);
	while (amount_dollars-- > 0)
	{
		input = check_input(input, envv);
		input = quote_handler(input);
	}
	input = cmd_table_handler(info, input);
	crop_redir(info);
	handle_struct(info);
	print_cmd_table(info->cmd_table);
	return (input);
}
