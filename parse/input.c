/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@students.42wolfsburg.de>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:11:12 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/16 07:14:20 by jtomala          ###   ########.fr       */
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
	new_input = malloc(ft_strlen(input) - var_len + ft_strlen(value) + 1);
	if (!new_input || !value)
		return (input);
	while (input[i] != '$')
		i++;
	printf("VAR_LEN: %d\n", var_len);
	i = ft_copy(new_input, input, i + 1);
	j = ft_copy(&new_input[i], value, 0);
	if (&input[i + var_len])
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
	t_list *tmp;

	i = 0;
	tmp = l_envv;
	while (tmp->next != NULL)
	{
		if (!ft_strncmp(tmp->content, str, ft_strlen(str)))
		{
			value = ft_split(tmp->content, '=');
			return (value[1]);
		}
		tmp = tmp->next;
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
			break ;
		}
		i++;					
		*counter = i;
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
	int var_len;

	var = get_value(ft_strchr(input, '$'), &var_len);
	if (var)
	{
		value = return_envv_val(info->envv, var + 1);
		input = modify_input(input, value, var_len);
	}
	else
	{
		free(var);
		return (input);
	}
	free(var);
	free(value);
	return (input);
}

/*
put envv in a struct and replace them with the actual values
*/
void handle_input(t_data *info, char *input, int counter)
{
	while (ft_strchr(input, '$'))
		input = check_input(info, input); //realloc input so no segfault can happen | flag for the while loop to protect
	info->cmd_table[counter] = malloc(sizeof(input));
	ft_copy(info->cmd_table[counter], input, 0);
	printf("[%d]%s\n", counter, info->cmd_table[counter]);
}

/*
handles the input given by the user and puts it into a struct
*/
void	copy_envv(t_list **l_envv, char **envv)
{
	t_list *tmp;
	int i;

	i = 1;
	(*l_envv)->content = envv[0];
	(*l_envv)->next = NULL;
	while (envv[i])
	{
		tmp = ft_lstnew(envv[i]);
		ft_lstadd_back(l_envv, tmp);
		i++;
	}
	//*l_envv = (*l_envv)->next;
}
