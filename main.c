/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:12:30 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/04/06 19:40:56 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_cmd(int *starting_index, char *str)
{
	//Find the command itself
	int w_size;
	int i;
	int first_size;
	first_size = *starting_index;
	w_size = 0;
	i = 0;
	while(str[*starting_index])
	{
		if(str[*starting_index] == ' ' || str[*starting_index] == '\t')
			*starting_index = *starting_index + 1;
		else
			break;
	}

	while(str[*starting_index])
	{
		if(str[*starting_index] != ' ' && str[*starting_index] != '\t')
		{
			w_size++;
		}else{
			break;
		}
		*starting_index = *starting_index + 1;
	}
	
	if(w_size == 0)
		return NULL;
	*starting_index -= w_size + 1;
	char *cmd = malloc(sizeof(char) * (w_size + 1));
	
	while(*starting_index < w_size + first_size)
	{
		*starting_index = *starting_index + 1;
		cmd[i++] = str[*starting_index];
	}
	cmd[i] = '\0';
	return cmd;
}
// char **create_command_table(char *str)
// {
// 	int i = 0;
// 	// int	quote_flag = 0; 
// 	while(str[i])
// 	{
// 		if(str[i] != '|')
// 		{
			
// 		}
// 		i++;
// 	}     
// }
int main(void)
{
	int starting_index = 0;
	char *wrd;
	int i = 0;
	while(i < 2)
	{
		wrd = find_cmd(&starting_index, "owdqokodqw Marek");
		printf("%s Index %d\n" , wrd, starting_index);
		if(!wrd)
			break;
		i++;
	}
	// printf("%s", find_cmd(0,"echo Marek\n"));
}