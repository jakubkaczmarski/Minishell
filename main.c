/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:12:03 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/16 17:11:18 by jtomala          ###   ########.fr       */
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
	info->envv = malloc(sizeof(t_list **));
	//if (copy_envv(&(info->envv), envv))
	//	return (1);
	printf("start %s...\n", argv[0]); //for testing
	//print_envv(info->envv, 0);
	handle_sigs_interactive(); //signals
	while (1)
	{
		input = readline("minishell>🦖");
		if (!input)
			break ;
		add_history(input);
		input = handle_input(info, input, envv);	
		if (!ft_strncmp(info->cmd_table[0], "exit", 5))
			break ;
		//builtin_handler(info);
		//manage_exec(info, envv);
		
		free(input);
		counter = 0;
		
		while (info->cmd_table[counter])
			free(info->cmd_table[counter++]);
		free(info->cmd_table);
	}

	ft_lstclear(&(info->envv), free);
	free(info);
	return (0);
}
