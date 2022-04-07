/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:11:12 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/07 17:00:40 by jtomala          ###   ########.fr       */
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
char *exchange_envv(t_data **info, char *str)
{
	char **split;
	char *envv;
	
	write(1, "G", 1);
	split = NULL;
	while ((*info)->envv != NULL)
	{
		envv = (*info)->envv->content;
		split = ft_split(envv, '=');
		if (split[0] == str)
			printf("REPLACE");
		(*info)->envv = (*info)->envv->next;
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
		var[0] += 1;
		printf("%s\n", var[0]);
		exchange_envv(&info, var[0]);
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
void copy_envv(t_data *info, char **envv)
{
	t_list *tmp;
	int i;

	i = 0;
	while (envv[i])
	{
		printf("%s\n", envv[i]);
		tmp = ft_lstnew(envv[i]);
		ft_lstadd_back(&(info->envv), tmp);
		//printf("%s\n", info->envv->content);
		i++;
	}
}
