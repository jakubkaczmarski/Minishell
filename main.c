/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:08:54 by jtomala           #+#    #+#             */
/*   Updated: 2022/06/07 00:50:01 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_error(void)
{
	printf("Input Error\n");
	return (1);
}

void	free_all(t_data *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (info->cmd[i].cmd[j])
	{
		while (info->cmd[i].cmd[j])
		{
			free_2d_array(info->cmd[i].cmd);
			free_2d_array(info->cmd[i].in);
			free_2d_array(info->cmd[i].out);
			i++;
		}
	}
	free_2d_array(info->cmd[i].cmd);
	free_2d_array(info->cmd[i].in);
	free_2d_array(info->cmd[i].out);
	free(info->cmd);
}

int	alternative_free(t_data *info)
{
	free_2d_array(info->env);
	delete_list(&info->envv);
	free(info);
	return (0);
}

/*
mallocs the data struct to safe some lines
*/
int	malloc_struct(t_data **info)
{
	*info = malloc(sizeof(t_data));
	if (!*info)
		return (1);
	return (0);
}

/*
@param argc amount of arguments
@param argv arguments as array
@param envv enviromental variables as array \
*/
int	main(int argc, char **argv, char **envv)
{
	t_data	*info;
	char	*input;

	if (argc != 1 || !argv[0])
		return (input_error());
	if (malloc_struct(&info) || copy_envv(&(info->envv), envv))
		return (1);
	handle_sigs_interactive();
	info->env = convert_env_list_to_str(&info->envv);
	while (1)
	{
		input = readline("minishell🦖>");
		if (!input)
			return (alternative_free(info));
		if (input[0] == '\0')
			continue ;
		add_history(input);
		input = handle_input(info, input);
		free_2d_array(info->env);
		info->env = convert_env_list_to_str(&info->envv);
		free(input);
		exec_stuff(info);
		free_all(info);
	}
	return (1);
}

	// end_free(input, info);