/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:12:03 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/03 15:21:19 by jkaczmar         ###   ########.fr       */
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

	counter = 0;
	info = malloc(sizeof(t_data *));
	info->cmd_table = malloc(sizeof(char **)); //protect against alloc-fail
	info->formated_cmds = malloc(sizeof(char **) * 1000);
	counter = 0;
	if (argc != 1)
		return (input_error());
	info->envv = malloc(sizeof(char **));
	if (!(info->envv))
		return (1);
	copy_envv((info->envv), envv);
	printf("%s", argv[0]); //for testing

	while (1)
	{
		input = readline("minishell>");
		if (!input || ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			break ;
		}
		add_history(input);
		input = handle_input(info, input, counter, envv);
		format_line(info, counter);
		builtin_handler(info, counter);
		free(input);
		counter++;
	}
	if(counter == -1)
		return 0;
	else
	{
		print_lines(info, counter);
		counter = 0;
		// while (info->cmd_table[counter + 1])
		// 	free(info->cmd_table[counter++]);
	}
	//lowercase user seg_faults
	//List are not freed
	delete_env_list(info);
	free(info->envv);
	free(info);
	return (0);
}
