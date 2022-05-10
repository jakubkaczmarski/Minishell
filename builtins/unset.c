/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@students.42wolfsburg.de>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 07:29:01 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/10 07:47:11 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void remove_in_envv(t_list **envv, char *var)
{
	t_list *curr;
	t_list *tmp;
	
	curr = *envv;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->content, var, ft_strlen(var)));
		{
			//safe the element in a var
			//set the pointer to the next element
			//free the var
		}
		curr = curr->next;
	}
}

/*
takes the variables that are given and removes them 
one by one from the list envv
*/
void unset_handler(t_data *info, int index)
{
	int		i;
	char	**variables;
	char	*var;

	i = 0;
	variables = ft_split(info->cmd_table[index], ' ');
	free(variables[0]);
	index = 1;
	while (variables[index])
	{
		while (variables[index][i] != '\0')
			i++;
		var = ft_substr(variables[index], 0, i);
		if (ft_isvalid(var))
			return ;
		remove_in_envv(&(info->envv), var);
		free(variables[index]);
		i = 0;
		index++;
	}
	free(variables);
}