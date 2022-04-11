/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:11:12 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/11 15:28:14 by jtomala          ###   ########.fr       */
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
char *exchange_envv(t_list *l_envv, char *str)
{
	int i;
	char **value;

	i = 0;
	while (l_envv->next != NULL)
	{
		//printf("COMPARE: %s with %s\n", l_envv->content, str);
		if (!ft_strncmp(l_envv->content, str, ft_strlen(str)))
		{
			value = ft_split(l_envv->content, '=');
			return (value[1]);
		}
		l_envv = l_envv->next;
		i++;
	}
	return (NULL);
}

/*
checks the input for enviromental variables
*/
char *check_input(t_data *info, char *input)
{
	char *var_start;
	char *var_end;
	char **var;
	char *value;
	
	var_start = ft_strchr(input, '$');
	var = NULL;
	var_end = malloc(sizeof(char *));
	value = malloc(sizeof(char *));
	if (var_start)
	{
		var = ft_split(var_start, ' ');
		var_end = &input[ft_strlen(var_start) + ft_strlen(var[0])];
		value = exchange_envv(info->envv, var[0] + 1);
		if (!value)
			return (input);
		input[ft_strchr(input, '$') - input] = '\0';
		input = ft_strjoin(input, value);
		input = ft_strjoin(input, var_end);
	}
	return (input);
	
}

/*
put envv in a struct and replace them with the actual values
*/
void handle_input(t_data **info, char *input, int counter)
{
	input = check_input(*info, input);
	(*info)->cmd_table[counter] = malloc(sizeof(input));
	(*info)->cmd_table[counter] = input;
	printf("[%d]%s\n", counter, (*info)->cmd_table[counter]);
	//execute_cmd(*info, counter);	
}

/*
handles the input given by the user and puts it into a struct
*/
void	copy_envv(t_list **l_envv, char **envv)
{
	t_list *tmp;
	int i;

	i = 0;
	while (envv[i])
	{
		tmp = ft_lstnew(envv[i]);
		ft_lstadd_back(l_envv, tmp);
		i++;
	}
	*l_envv = (*l_envv)->next;
}
