/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:08:54 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/29 15:09:40 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int input_error()
{
	printf("Input Error\n");
	return (1);
}

void free_all(t_data *info, int counter)
{
	int i = 0;
	int j;
		j = 0;
		while(i < info->amount_cmd)
		{
			while(info->cmd[i].cmd[j])
			{
				free(info->cmd[i].cmd[j]);
				j++;
			}
			j = 0;
			while(info->cmd[i].in[j])
			{
				free(info->cmd[i].in[j]);
				j++;
			}
			j = 0;
			while(info->cmd[i].out[j])
			{
				free(info->cmd[i].out[j]);
				j++;
			}
			// free(info->cmd[i].command_path);
			// free(info->cmd[i].gen_path);
			i++;
		}
		while (info->cmd_table[counter])
			free(info->cmd_table[counter++]);
		
}

void update_env(t_data *info)
{
	char **str = convert_env_list_to_str(&info->envv);
	// int i = 0;
	info->env = add_env(str);
}

void end_free(char *input, t_data *info)
{
	if(!input)
	{
		free(input);
		free(info);
	}else{
		free(info->cmd_table[0]);
		ft_lstclear(&(info->envv), free);
		free(info->envv);
		free(info);
	}
}
/*
@param argc amount of arguments
@param argv arguments as array
@param envv enviromental variables as array \
*/
int main(int argc, char **argv, char **envv)
{
	t_data *info;
	char *input;
	int counter;
	if(argv[0]){};
	if (argc != 1)
		return (input_error());
	info = malloc(sizeof(t_data *));
	if (!info)
		return (1);
	info->ret_val = 0;
	if (copy_envv(&(info->envv), envv))
		return (1);
	handle_sigs_interactive(); //signal
	while (1)
	{
		input = readline("minishell🦖>");
		if (!input)
			break ;
		if(input[0] == '\0')
			continue;
		update_env(info);
		add_history(input);
		input = handle_input(info, input, envv);	
		if(!input)
			break;
		exec_stuff(info);
		free(input);
		counter = 0;
		free_all(info, counter);
	}
	end_free(input, info);
	return (0);
}
