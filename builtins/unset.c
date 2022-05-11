/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 07:29:01 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/11 08:56:30 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_in_envv(t_list **envv, char *var)
{
	t_list *curr;
	char **var_val;
	t_list *tmp;
	
	curr = *envv;
	while (curr->next != NULL)
	{
		var_val = ft_split(curr->next->content, '=');
		//printf("compare: %s with %s\n", var_val[0], var);
		if (!ft_strncmp(var_val[0], var, ft_strlen(var)))
		{
			printf("element found!\n");
			tmp = curr;
			curr->next = curr->next->next;
			//free(tmp);
			free(var_val);
			return ;
		}
		free(var_val);
		curr = curr->next;
	}
}

/*
takes the variables that are given and removes them 
one by one from the list envv
*/
void	unset_handler(t_data *info, int index)
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
		// if (ft_isvalid(var))
		// 	return ;
		printf("Detected: %s\n", var);
		remove_in_envv(&(info->envv), var);
		free(variables[index]);
		i = 0;
		index++;
	}
	free(variables);
}