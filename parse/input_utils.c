/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@students.42wolfsburg.de>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:07:23 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/26 06:10:53 by jtomala          ###   ########.fr       */
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
	int	i;

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
takes the input and the value of envv and replaces
the variable by their actual value
*/
char	*modify_input(char *input, char *value, int var_len)
{
	int		i;
	int		j;
	int		flag;
	char	*new_input;

	i = 0;
	flag = 0;
	new_input = ft_calloc(sizeof(char *),
			(ft_strlen(input) + ft_strlen(value) + 1));
	if (!new_input)
		return (input);
	while (input[i])
	{
		if (input[i] == '$' && ((input[i - 1] != '\'') \
			|| (input[i - 1] == '\'' && input[i - 2] == '"')))
			break ;
		i++;
	}
	i = ft_copy(new_input, input, i + 1);
	j = ft_copy(&new_input[i], value, 0);
	if (&input[i + var_len])
		ft_copy(&new_input[i + j], &input[i + var_len], 0);
	free(input);
	return (new_input);
}

/*
returns the value of the variable that is given in str.
If none is found NULL gets returned
*/
char	*return_envv_val(char **envv, char *str)
{
	int		i;
	int		counter;
	char	*value;

	i = 0;
	counter = 1;
	value = NULL;
	while (envv[i])
	{
		if (!ft_strncmp(envv[i], str, ft_strlen(str)))
		{
			while (envv[i][counter] != '=')
				counter++;
			value = ft_substr(envv[i], counter + 1,
					ft_strlen(&envv[i][counter]));
			return (value);
		}
		i++;
	}
	return (NULL);
}

/*
function should remove the brackets. e.g.: ${USER} -> $USER
*/
char	*ft_crop_brackets(char *var)
{
	char	*new_var;

	new_var = ft_calloc(sizeof(char *), ft_strlen(var) + 1);
	ft_copy(new_var, var, 1);
	ft_copy(&new_var[1], &var[2], ft_strlen(&var[2]));
	free(var);
	return (new_var);
}

/*
modifies the value by cutting the rest off. Everything after whitespace.
*/
char	*get_value(char *var, int *counter)
{
	int		i;
	char	*variable;

	i = 1;
	variable = NULL;
	if (!var)
		return (NULL);
	while (var[i])
	{
		if (!ft_isalnum(var[i]))
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
	variable = ft_substr(var, 0, i);
	*counter = i;
	if (ft_strchr(variable, '{'))
		variable = ft_crop_brackets(variable);
	return (variable);
}
