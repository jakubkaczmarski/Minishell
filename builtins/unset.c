/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 07:29:01 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/12 08:41:49 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_in_envv(t_list **envv, char *var)
{
	t_list *curr;
	t_list *tmp;
	char **var_val;
	int flag;
	
	curr = *envv;
	flag = 0;
	while (curr->next != NULL)
	{
		var_val = ft_split(curr->next->content, '=');
		if (!ft_strncmp(var_val[0], var, ft_strlen(var)) \
			&& !var_val[0][ft_strlen(var)])
		{
			tmp = curr->next;
			free(tmp->content);
			free(tmp);
			curr->next = curr->next->next;
			flag = 1;
		}
		free(var_val[0]);
		free(var_val[1]);
		free(var_val);
		if (flag == 1)
			return ;
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
		remove_in_envv(&(info->envv), var);
		free(variables[index]);
		free(var);
		i = 0;
		index++;
	}
	free(variables);
}
