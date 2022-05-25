/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:08:54 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/25 17:45:00 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int input_error()
{
	printf("Input Error\n");
	return (1);
}

void print_envv(t_list *envv, int flag)
{
	if (!envv)
		return ;
	while (envv != NULL)
	{
		if (flag == 1)
			printf("delcare -x %s\n", envv->content);
		else
			printf("%s\n", envv->content);
		envv = envv->next;
	}
}

char **add_env(char **env)
{
	char **ret;
	int i = 0;
	while(env[i])
	{
		i++;
	}
	ret = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while(env[i])
	{
		ret[i] = ft_strdup(env[i]);
		i++;
	}
	return ret;
}


void free_all(t_data *info)
{
	int i = 0;
	int j;
		j = 0;
		while(info->cmd[i].cmd[j])
		{
			free(info->cmd[i].cmd[j]);
			j++;
		}
		j = 0;
		while(info->cmd[i].in[j])
		{
			free(info->cmd[i].in[j]);
		}
		j = 0;
		while(info->cmd[i].out[j])
		{
			free(info->cmd[i].out[j]);
		}
		free(info->cmd[i].command_path);
		free(info->cmd[i].gen_path);
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

	if (argc != 1)
		return (input_error());
	info = malloc(sizeof(t_data *));
	if (!info)
		return (1);
	info->ret_val = 0;
	printf("Start %s\n", argv[0]);
	

	if (copy_envv(&(info->envv), envv))
		return (1);
	
	info->env = add_env(envv);
	handle_sigs_interactive(); //signal
	while (1)
	{

		input = readline("minishell🦖>");
		if (!input)
			break ;
		if(input[0] == '\0')
			continue;
		add_history(input);
		// info->env = envv;
		
		input = handle_input(info, input, envv);	
		if(!input)
			break;
		// exec_stuff(info);	
		// manage_exec(info, envv);
		// printf("input: %s\n", input);
		free(input);
		counter = 0;
		// free_all(info);
		while (info->cmd_table[counter])
			free(info->cmd_table[counter++]);	
	}
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
	return (0);
}
