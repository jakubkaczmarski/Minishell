/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:11:12 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/14 10:28:20 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
copy function that puts two strings together. If len == 0 then everyrthing gets copied,
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
	while (input[i])
		if (input[i++] == '$')
			break ;
	printf("VAR_LEN: %d\n", var_len);
	i = ft_copy(new_input, input, i);
	j = ft_copy(&new_input[i], value, 0);
	ft_copy(&new_input[i + j], &input[i + var_len], 0);
	return (new_input);
}

/*
returns the value of the variable that is given in str. If none is found NULL gets returned
*/
char *return_envv_val(t_list *l_envv, char *str)
{
	int i;
	char **value;

	i = 0;
	while (l_envv->next != NULL)
	{
		if (!ft_strncmp(l_envv->content, str, ft_strlen(str)))
		{
			value = ft_split(l_envv->content, '=');
			return (value[1]);
		}
		l_envv = l_envv->next;
		i++;
	}
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
		}
		i++;					
	}
	return (value);
}

/*
is checking the input for $-sign and replaces the variable by the value
*/
char *check_input(t_data *info, char *input)
{
	char *var;
	char *value;
	int i;
	int counter;

	var = get_value(ft_strchr(input, '$'), &counter);
	value = malloc(sizeof(char *));
	if (!value)
		return (input);
	i = 1;
	if (var)
	{
		value = return_envv_val(info->envv, var + 1);
		input = modify_input(input, value, counter);
	}
	free(var);
	free(value);
	return (input);
}

/*
put envv in a struct and replace them with the actual values
*/
void handle_input(t_data **info, char *input, int counter)
{
	input = check_input(*info, input);
	(*info)->cmd_table[counter] = malloc(sizeof(input));
	(*info)->cmd_table[counter] = input;
	printf("[%d]%s\n", counter, (*info)->cmd_table[counter]);
}

/*
handles the input given by the user and puts it into a struct
*/
void	copy_envv(t_list **l_envv, char **envv)
{
	t_list *tmp;
	int i;

	i = 0;
	while (envv[i])
	{
		tmp = ft_lstnew(envv[i]);
		ft_lstadd_back(l_envv, tmp);
		i++;
	}
	*l_envv = (*l_envv)->next;
}
