/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:11:12 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/21 08:17:34 by jtomala          ###   ########.fr       */
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
	new_input = malloc(ft_strlen(input) + ft_strlen(value) + 1);
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
		if (!ft_strncmp(envv[i], str, ft_strlen(str))) //SEGFAULTs
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
modifies the value by cutting the rest off. Everything after whitespace.
*/
char *get_value(char *var, int *counter)
{
	int i;
	char *value;

	i = 0;
	value = malloc(sizeof(char *));
	if (!var)
		return (NULL);
	while (var[i])
	{
		if (var[i] == ' ')
		{
			value = ft_memcpy(value, var, i);
			*counter = i;
			return (value);
		}
		i++;					
		*counter = i;
	}
	return (value);
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
		value = return_envv_val(envv, var + 1); //SEGFAULT
		input = modify_input(input, value, var_len);
	}
	//if (value)
	//	free(value);
	if (var)
		free(var);
	return (input);
}

/*
put envv in a struct and replace them with the actual values
*/
char *handle_input(t_data *info, char *input, int counter, char **envv)
{
	//while (ft_strchr(input, '$'))
	input = check_input(input, envv); // flag for the while loop to protect
	info->cmd_table[counter] = malloc(sizeof(input + 1));
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
