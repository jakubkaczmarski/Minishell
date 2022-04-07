/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:11:12 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/07 12:20:38 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
handles the input given by the user and puts it into a struct
*/
void handle_input(t_data *info, char *input, int counter)
{
	info->cmd_table[counter] = malloc(sizeof(input));
	info->cmd_table[counter] = input;
	printf("[%d]%s\n", counter, info->cmd_table[counter]);
}

/*
put envv in a struct and replace them with the actual values
*/
void copy_envv(t_data *info, char **envv)
{
	t_list *tmp;
	int i;

	i = 0;
	while (envv[i])
	{
		tmp = ft_lstnew(envv);
		ft_lstadd_back(&info->envv, tmp);
		printf("%s\n", envv[i]);
		i++;
	}
	//replace_envv(info);
}

/*
if there is a variable in argv then the function searchs for this 
in envv and replace it by the value
*/
void replace_envv()
{

}
