/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:07:25 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/17 17:12:26 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
splits the list by '=' and prints it it out with
'declare -x' and the value in quotes
*/
void	split_and_print(char *smallest)
{
	int		i;
	char	**var_val;

	i = 2;
	var_val = ft_split(smallest, '=');
	printf("declare -x %s=\"", var_val[0]);
	printf("%s", var_val[1]);
	free(var_val[0]);
	free(var_val[1]);
	while (var_val[i])
	{
		printf("=%s", var_val[i]);
		free(var_val[i]);
		i++;
	}
	printf("\"\n");
	free(var_val);
}

/*
goes trough the list and sets the index to 0
*/
void	indexing(t_list **curr)
{
	t_list *tmp;

	tmp = *curr;
	while (tmp->next != NULL)
	{
		tmp->index = 0;
		tmp = tmp->next;
	}
}

/*
sorts the list and prints it out in alphabetical order with
a specific shema
*/
void	sort_list(t_list **envv)
{
	t_list	*curr;
	t_list	*smallest;
	int		i;
	int		amount_elements;

	// smallest = malloc(sizeof(t_list *));
	// curr = malloc(sizeof(t_list *));
	// if (!smallest || !curr)
	// 	return ;
	//indexing(envv);
	smallest = *envv;
	curr = *envv;
	i = 1;
	//print_envv(*envv, 0);
	amount_elements = ft_lstsize(curr);
	while (i < amount_elements)
	{
		while (curr->next != NULL)
		{
			if (ft_strncmp(curr->content, smallest->content, \
				ft_strlen(smallest->content)) < 0 && curr->index != -1)
				smallest = curr;
			curr = curr->next;
			while (curr->index == -1)
				curr = curr->next;
		}
		i++;
		smallest->index = -1;
		split_and_print(smallest->content);
		smallest = *envv;
		while (smallest->index == -1)
			smallest = smallest->next;
		curr = *envv;
	}
}
