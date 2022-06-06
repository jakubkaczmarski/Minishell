/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:07:25 by jtomala           #+#    #+#             */
/*   Updated: 2022/06/06 09:18:43 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
resets the index of the list
*/
void	indexing(t_list *envv)
{
	t_list	*tmp;

	tmp = envv;
	while (tmp != NULL)
	{
		tmp->index = 0;
		tmp = tmp->next;
	}
}

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

void	sort_list_helper(t_list *curr, t_list *smallest)
{
	if (ft_strncmp(curr->content, smallest->content,
			ft_strlen(smallest->content)) < 0 && curr->index != -1)
		smallest = curr;
}

/*
sorts the list and prints it out in alphabetical order with
a specific shema
*/
void	sort_list(t_list *envv)
{
	t_list	*curr;
	t_list	*smallest;
	int		amount_elements;

	smallest = envv;
	curr = envv;
	amount_elements = ft_lstsize(curr);
	while (amount_elements-- > 0)
	{
		while (curr->next != NULL)
		{
			sort_list_helper(curr, smallest);
			curr = curr->next;
			while (curr->index == -1 && curr->next != NULL)
				curr = curr->next;
		}
		smallest->index = -1;
		split_and_print(smallest->content);
		smallest = envv;
		while (smallest->index == -1 && smallest->next != NULL)
			smallest = smallest->next;
		curr = envv->next;
	}
	indexing(envv);
}
