/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:11:12 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/21 12:00:28 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
copy function that puts two strings together.
If len == 0 then everyrthing gets copied,
otherwise len == how many characters of src should get copied.
*/
int	ft_copy(char *dst, char *src, int len)
{
	int i;

	i = 0;
	if (len == 0)
	{
		while (src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	else
	{
		len--;
		while (i < len && src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[i] = '\0';
	return (i);
}

/*
takes the input and the value of envv and replaces the variable by their actual value
*/
char *modify_input(char *input, char *value, int var_len)
{
	int i;
	int j;
	char *new_input;

	i = 0;
	new_input = ft_calloc(sizeof(char *), ft_strlen(input) + ft_strlen(value) + 1);
	if (!new_input)
	{
		printf("allocation failed\n");
		return (input);
	}
	while (input[i] != '$')
		i++;
	i = ft_copy(new_input, input, i + 1); 
	j = ft_copy(&new_input[i], value, 0);
	if (&input[i + var_len])
		ft_copy(&new_input[i + j], &input[i + var_len], 0);
	free(input);
	return (new_input);
}

/*
returns the value of the variable that is given in str. If none is found NULL gets returned
*/
char *return_envv_val(char **envv, char *str) 
{
	int i;
	int counter;
	char *value;

	i = 0;
	counter = 0;
	value = malloc(sizeof(char *));
	if (!value)
		return (NULL);
	while (envv[i])
	{
		if (!ft_strncmp(envv[i], str, ft_strlen(str)))
		{
			while (envv[i][counter] != '=')
				counter++;
			ft_copy(value, &(envv[i][counter + 1]), 0);
			return (value);
		}
		i++;
	}
	printf("returned NULL");
	return (NULL);
}

/*
function should remove the brackets. e.g.: {USER} -> USER
*/
char *ft_crop_brackets(char *var)
{
	char *new_var;

	new_var = ft_calloc(sizeof(char *), ft_strlen(var) + 1);
	ft_copy(new_var, var, 1);
	ft_copy(&new_var[1], &var[2], ft_strlen(&var[2]));
	free(var);
	return (new_var);
}

/*
modifies the value by cutting the rest off. Everything after whitespace.
*/
char *get_value(char *var, int *counter)
{
	int i;
	char *variable;

	i = 0;
	variable = NULL;
	if (!var)
		return (NULL);
	while (var[i])
	{
		if (var[i] == ' ') //every non alphnumeric character
		{
			variable = ft_substr(var, 0, i);
			*counter = i;
			if (ft_strchr(variable, '{'))
				variable = ft_crop_brackets(variable);
			return (variable);
		}
		i++;					
		*counter = i;
	}
	return (variable);
}

/*
is checking the input for $-sign and replaces the variable by the value
*/
char *check_input(char *input, char **envv)
{
	char *var;
	char *value;
	int var_len;

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
char *handle_input(t_data *info, char *input, int counter, char **envv)
{
	int i;
	int amount_dollars;

	i = 0;
	amount_dollars = 0;
	while (input[i])
		if (input[i++] == '$')
			amount_dollars++;
	while (amount_dollars-- > 0)
	{
		input = check_input(input, envv); // flag for the while loop to protect
		printf("input: %s\n", input);
	}
	info->cmd_table[counter] = ft_calloc(sizeof(char *), ft_strlen(input) + 1);
	ft_copy(info->cmd_table[counter], input, 0);
	printf("[%d]%s\n", counter, info->cmd_table[counter]);
	return (input);
}

/*
handles the input given by the user and puts it into a struct
*/
void	copy_envv(t_list *l_envv, char **envv)
{
	t_list *tmp;
	int i;

	i = 1;
	if (envv)
	{
		(l_envv)->content = envv[0];
		(l_envv)->next = NULL;
		while (envv[i])
		{
			tmp = ft_lstnew(envv[i]);
			ft_lstadd_back(&l_envv, tmp);
			i++;
		}
	}
}
