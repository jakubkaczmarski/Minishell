/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@students.42wolfsburg.de>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:07:25 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/15 18:59:34 by jtomala          ###   ########.fr       */
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
void	indexing(t_list *curr)
{
	while (curr->next != NULL)
	{
		curr->index = 0;
		curr = curr->next;
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

	curr = *envv;
	smallest = *envv;
	i = 1;
	indexing(curr);
	amount_elements = ft_lstsize(*envv);
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
