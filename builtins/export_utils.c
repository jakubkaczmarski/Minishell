/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@students.42wolfsburg.de>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:07:25 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/15 10:24:01 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
sorts or prints out the envv list in alphabetical order
*/
// void sort_list(t_list *envv)
// {
// 	t_list *dub;

// 	while (envv->next != NULL)
// 	{
// 		dub = malloc(sizeof(t_list *));
// 		//ft_copy(dub->content, envv->content, 0);
// 		dub->content = envv->content;
// 		dub->next = envv->next;
// 		dub = dub->next;
// 		envv = envv->next;
// 	}
// 	while (dub->next != NULL)
// 	{
// 		printf("%s\n", dub->content);
// 		dub = dub->next;
// 	}
// }

void split_and_print(char *smallest)
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

void indexing(t_list *curr)
{
	while (curr->next != NULL)
	{
		curr->index = 0;
		printf("index: %d => %s\n", curr->index, curr->content);
		curr = curr->next;
	}
}

void sort_list(t_list **envv)
{
	t_list *curr;
	t_list *smallest;
	int i;
	int amount_elements;
	curr = *envv;
	smallest = *envv;
	i = 1;
	amount_elements = ft_lstsize(*envv);
	curr = *envv;
	//printf("amount: %d\n", amount_elements);
	while (i < amount_elements)
	{
		//printf("Round: %d\n", i);
		while (curr->next != NULL)
		{
			//printf("compare %s[%d] with %s\n", curr->content, curr->index, smallest->content);
			if (ft_strncmp(curr->content, smallest->content, \
				ft_strlen(smallest->content)) < 0 && curr->index != -1)
			{
				//printf("triggert\n");
				smallest = curr;
			}
			curr = curr->next;
			while (curr->index == -1)
				curr = curr->next;
		}
		//printf("after-while-crocodikehdhd\n");
		i++;
		smallest->index = -1;
		split_and_print(smallest->content);
		//printf("declare -x %s\n", smallest->content);
		smallest = *envv;
		while (smallest->index == -1)
			smallest = smallest->next;
		curr = *envv;
	}
}


// /*
// searchs for the hightest element in the list
// */
// static t_list	*ft_highest(t_list *stack_a)
// {
// 	t_list	*highest;

// 	highest = stack_a;
// 	while (stack_a->next != NULL)
// 	{
// 		if (ft_strncmp(stack_a->content, highest->content, ft_strlen(highest->content)) > 0)//(stack_a->content > highest->content)
// 			highest = stack_a;
// 		stack_a = stack_a->next;
// 	}
// 	return (highest);
// }

// /*
// counts the element and set the default index (-1)
// */
// static int	ft_count_and_init(t_list *stack_a)
// {
// 	t_list	*tmp;
// 	int		counter;

// 	tmp = stack_a;
// 	counter = 0;
// 	while (tmp->next != NULL)
// 	{
// 		counter++;
// 		tmp->index = -1;
// 		tmp = tmp->next;
// 	}
// 	return (counter);
// }

// static int	indexing(t_list *stack_a)
// {
// 	t_list	*tmp;
// 	t_list	*piv;
// 	int		counter;
// 	int		i;

// 	tmp = stack_a;
// 	counter = ft_count_and_init(stack_a);
// 	piv = ft_highest(stack_a);
// 	i = 1;
// 	while (i <= counter)
// 	{
// 		while (tmp->next != NULL)
// 		{
// 			if (ft_strncmp(tmp->content, piv->content, ft_strlen(piv->content)) < 0 && (tmp->index) == -1)
// 				piv = tmp;
// 			tmp = tmp->next;
// 		}
// 		piv->index = i++;
// 		tmp = stack_a;
// 		//printf("%s\n", piv->content);
// 		piv = ft_highest(stack_a);
// 	}
// 	return (counter);
// }

// void sort_list(t_list *envv)
// {
// 	indexing(envv);
// }