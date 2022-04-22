/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:12:03 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/22 13:21:02 by jtomala          ###   ########.fr       */
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

	info = malloc(sizeof(t_data *));
	info->cmd_table = malloc(sizeof(char **)); //protect against alloc-fail
	counter = 0;
	if (argc != 1)
		return (input_error());
	info->envv = malloc(sizeof(envv));
	if (!(info->envv))
		return (1);
	copy_envv((info->envv), envv);
	printf("%s", argv[0]); //for testing
	while (1)
	{
		input = readline("minishell>");
		if (!input)
			break ;
		add_history(input);
		//print_envv(envv);
		input = handle_input(info, input, counter, envv);
		builtin_handler(info);
		free(input);
		printf("-------------------------------------------------\n");
		counter++;
	}
	counter = 0;
	while (info->cmd_table[counter])
		free(info->cmd_table[counter++]);
	free(info->envv);
	free(info);
	return (0);
}
