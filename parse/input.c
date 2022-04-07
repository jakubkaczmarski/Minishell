/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:11:12 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/07 13:32:51 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
put envv in a struct and replace them with the actual values
*/
void copy_envv(t_list **lst_envv, char **envv)
{
	t_list *tmp;
	int i;

	i = 0;
	while (envv[i])
	{
		tmp = ft_lstnew(envv);
		ft_lstadd_back(lst_envv, tmp);
		i++;
	}
}

/*
handles the input given by the user and puts it into a struct
*/
void handle_input(t_data **info, char *input, int counter)
{
	(*info)->cmd_table[counter] = malloc(sizeof(input));
	(*info)->cmd_table[counter] = input;
	printf("[%d]%s\n", counter, (*info)->cmd_table[counter]);
	replace_envv(*info, input);
}

void check_for_var(t_data *info, char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
			printf("FOUND A $ %s\n", info->envv->content);
		i++;
	}
}

/*
if there is a variable in argv then the function searchs for this 
in envv and replace it by the value
*/
void replace_envv(t_data *info, char *input)
{
	check_for_var(info, input);
}
