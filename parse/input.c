/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:11:12 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/12 18:37:53 by jtomala          ###   ########.fr       */
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
// char *check_input(t_data *info, char *input)
// {
// 	char *var_start;
// 	char **var;
// 	char *value;
// 	int i;
	
// 	var_start = ft_strchr(input, '$');
// 	var = NULL;
// 	value = malloc(sizeof(char *));
// 	i = 1;
// 	if (var_start)
// 	{
// 		var = ft_split(var_start, ' ');
// 		value = exchange_envv(info->envv, var[0] + 1);
// 		if (!value)
// 			return (input);
// 		input[ft_strchr(input, '$') - input] = '\0';
// 		input = ft_strjoin(input, value);
// 		input = ft_strjoin(input, " ");
// 		while (var[i])
// 		{
// 			input = ft_strjoin(input, var[i++]);
// 			input = ft_strjoin(input, " ");
// 		}
// 	}
// 	return (input);
// }

char *get_value(char *input, int *counter)
{
	int i;

	i = 0;
	if (!input)
		return (NULL);
	while(input[i])
	{
		if (input[i] == ' ')
			while (input[i])
				input[i++] = '\0';
		i++;
	}
	*counter = i + 1;
	return (input);
}

char *modify_input(char *input, char *value, int counter, int len)
{
	int i;
	int j;
	char *safe_beg;
	char *safe_end;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			safe_beg = ft_substr(input, i, i);
			safe_end = safe_beg;
			printf("SAFE_BEG: %s%d\n", safe_beg, counter); //HERE IS THE PROBLEM
			printf("SAFE_END: %s\n", safe_end);
			while (j < len)
				input[i++] = value[j++];
		}
		i++;
	}
	j = 0;
	while (safe_end[j])
		input[i++] = safe_end[j++];
	input[i] = '\0';
	return (input);
}

char *check_input(t_data *info, char *input)
{
	char *var;
	char *value;
	int i;
	int counter;

	var = get_value(ft_strchr(input, '$'), &counter);
	printf("INPUT: %s\n", input);
	value = malloc(sizeof(char *));
	if (!value)
		return (input);
	i = 1;
	if (var)
	{
		value = exchange_envv(info->envv, var + 1);
		input = modify_input(input, value, counter, ft_strlen(value));
	}
	free(value);
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
