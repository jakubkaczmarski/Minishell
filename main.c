/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:12:03 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/07 16:50:31 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int input_error()
{
	printf("Input Error\n");
	return (1);
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

	info = malloc(sizeof(t_data));
	info->cmd_table = malloc(sizeof(char **));
	counter = 0;
	if (argc != 1)
		return (input_error());
	copy_envv(info, envv);
	printf("%s", argv[0]); //for testing
	while (1)
	{
		input = readline("minishell>");
		if (!input)
			break ;
		handle_input(&info, input, counter);
		add_history(input);
		counter++;
		free(input);
	}
	free(info->cmd_table);
	free(info->envv);
	free(info);
	return (0);
}
