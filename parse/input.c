/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:11:12 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/07 14:45:39 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*
Split command and arguments
*/
// void execute_cmd(t_data *info, int current_index)
// {
// 	if(current_index == 0)
// 	printf("%s", info->envv->content);
// }

/*
takes a variable(name) and gives its value back
*/
char *exchange_envv(t_data *info, char *str)
{
	char **split;
	
	split = NULL;
	while (info->envv->next != NULL)
	{
		split = ft_split(info->envv->content, '=');
		if (split[0] == str)
			printf("REPLACE");
		info->envv = info->envv->next;
	}
	return (split[1]);
}

/*
checks the input for enviromental variables
*/
void check_input(t_data *info, char *input)
{
	char *var_start;
	char **var;
	
	var_start = ft_strchr(input, '$');
	var = NULL;
	if (var_start != NULL)
	{
		var = ft_split(var_start, ' ');
		printf("%s\n", var[0]);
		exchange_envv(info, var[0]);
	}
	
}

/*
put envv in a struct and replace them with the actual values
*/
void handle_input(t_data **info, char *input, int counter)
{
	check_input(*info, input);
	(*info)->cmd_table[counter] = malloc(sizeof(input));
	(*info)->cmd_table[counter] = input;
	printf("[%d]%s\n", counter, (*info)->cmd_table[counter]);
	//execute_cmd(*info, counter);	
}

/*
handles the input given by the user and puts it into a struct
*/
void copy_envv(t_data **info, char **envv)
{
	t_list *tmp;
	int i;

	i = 0;
	while (envv[i])
	{
		tmp = ft_lstnew(envv);
		ft_lstadd_back(&info[0]->envv, tmp);
		//printf("%s\n", envv[i]);
		i++;
	}
}

