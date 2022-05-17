/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:43:50 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/17 19:13:11 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
checks if the input is alphanum and _ . ,
*/
int	ft_isvalid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
			i++;
		else if ((str[i] >= 48 && str[i] <= 57) || str[i] == 123 \
			|| str[i] == 125)
			i++;
		else if (str[i] == 95 || str[i] == 46 || str[i] == 44 || str[i] == 61)
			i++;
		else
		{
			printf("export: '%s': not a valid identifier\n", str);
			return (1);
		}
	}
	return (0);
}

/*
counts how many characters are until the given character
*/
int	ft_strint(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

/*
inserts the variable and this value at the end of the list.
Except the element already exists then replace it
*/
void	export_in_envv(t_list **envv, char *var_val)
{
	t_list	*tmp;
	t_list	*element;

	tmp = *envv;
	element = ft_lstnew(var_val);
	if (!element)
		return ;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->content, element->content, \
			ft_strint(element->content, '=')))
		{
			free(tmp->content);
			tmp->content = element->content;
			free(element);
			return ;
		}
		tmp = tmp->next;
	}
	ft_lstadd_back(envv, element);
}

/*
'export' is 7 characters long so look after that for the 
variable and store it. The variable ends at the equal sign 
so after that comes the value, store it as well
*/
void	export_handler(t_data *info, int index)
{
	int		i;
	char	*var_val;
	char	**variables;

	i = 0;
	variables = ft_split(info->cmd_table[index], ' ');
	free(variables[0]);
	index = 1;
	while (variables[index])
	{
		while (variables[index][i] != '\0')
			i++;
		var_val = ft_substr(variables[index], 0, i);
		if (ft_isvalid(var_val))
			return ;
		export_in_envv(&(info->envv), var_val);
		free(variables[index]);
		i = 0;
		index++;
	}
	if (index == 1)
		sort_list(&(info->envv));
	free(variables);
}
