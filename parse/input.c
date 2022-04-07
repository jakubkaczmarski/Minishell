/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:11:12 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/07 13:37:36 by jkaczmar         ###   ########.fr       */
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
handles the input given by the user and puts it into a struct
*/
void handle_input(t_data **info, char *input, int counter)
{
	(*info)->cmd_table[counter] = malloc(sizeof(input));
	(*info)->cmd_table[counter] = input;
	// execute_cmd(*info, counter);	
}

/*
put envv in a struct and replace them with the actual values
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
