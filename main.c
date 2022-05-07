/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:12:03 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/07 15:24:17 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int input_error()
{
	printf("Input Error\n");
	return (1);
}

// void print_envv(t_list *envv)
// {
// 	if (!envv)
// 		return ;
// 	printf("==> %p\n", envv);
// 	while (envv->next != NULL)
// 	{
// 		printf("=> %s\n", envv->content);
// 		printf("==> %p\n", envv->next);
// 		envv = envv->next;
// 	}
// }

void print_envv(char **envv)
{
	int i;

	i = 0;
	if (!envv)
		return ;
	while (envv[i])
		printf("=> %s\n", envv[i++]);
}

/*
@param argc amount of arguments
@param argv arguments as array
@param envv enviromental variables as array
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
	if (copy_envv((info->envv), envv))
		return (1);
	printf("%s", argv[0]); //for testing
	
	while (1)
	{
		input = readline("minishell>");
		if (!input)
			break ;
		add_history(input);
		//print_envv(envv);
		input = handle_input(info, input, envv);	
		if (!ft_strncmp(info->cmd_table[0], "exit", 5))
		{
			break ;
		}
		//builtin_handler(info)

		manage_exec(info, envv);
		printf("-------------------------------------------------\n");
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
