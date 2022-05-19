/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:59:32 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/19 16:30:16 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*
<something.txt
< something.txt
<<something.txt
go though the string and the first word after the redirect is the filename
for each redirect you have to have one index in the array
if there is <sth then insert a space: < sth
*/
int redirect_input(t_cmd *cmd, char *string)
{
	int	i;
	int	j;
	int	start;
	int	index;

	i = 0;
	j = 0;
	start = 0;
	index = 0;
	while (string[i])
	{
		if (string[i + j] == '<')
		{
			start = i;
			if (string[i + (++j)] == ' ')
				i++;
				//string = insert_space(string, i);
			while (string[i + j] != ' ')
				j++;
			cmd->in[index] = ft_substr(string, start, j);
			printf("in_redirect[%d]: %s\n", index, cmd->in[index]);
			index++;
		}
		i += j;
		j = 0;
		i++;
	}
	return (index);
}

void handle_struct(t_data *info)
{
	int i;
	int amount_red;

	i = 0;
	amount_red = 0;
	//execute command by command and call the functions in a loop
	info->cmd = malloc(sizeof(t_cmd *));
	info->cmd->in = malloc(sizeof(char **));
	info->cmd->out = malloc(sizeof(char **));
	info->cmd->cmd = malloc(sizeof(char **));
	while (info->cmd_table[i])
	{
		printf("------ROUND %d--------\n", i);
		info->cmd->in[i] = malloc(sizeof(char *));
		amount_red += redirect_input(&(info->cmd[i]), info->cmd_table[i]);
		//redirect_output();
		
		i++;
	}


	


	
}