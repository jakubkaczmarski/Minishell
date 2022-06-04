/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:08:54 by jtomala           #+#    #+#             */
/*   Updated: 2022/06/05 00:44:15 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		input_error()
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
	// while (info->cmd_table[counter])
	// 	free(info->cmd_table[counter++]);
	while (i < info->amount_cmd)
	{
		while (info->cmd[i].cmd[j])
		{
			free(info->cmd[i].cmd[j]);
			j++;
		}
		j = 0;
		while (info->cmd[i].in[j])
		{
			free(info->cmd[i].in[j]);
			j++;
		}
		j = 0;
		while (info->cmd[i].out[j])
		{
			free(info->cmd[i].out[j]);
			j++;
		}
		i++;
	}

}

void	update_env(t_data *info)
{
	// int i = 0;
	// info->env =;
	// printf("Updating \n");
	// print_envv(&info->envv, 0);
	info->env =  convert_env_list_to_str(&info->envv);
	// free_2d_array(str);
}

void	end_free(char *input, t_data *info)
{
	if (!input)
	{
		free(input);
		free(info);
	}
	else
	{
		free(info->cmd_table[0]);
		ft_lstclear(&(info->envv), free);
		free(info->envv);
		free(info);
	}
}

/*
mallocs the data struct to safe some lines 
*/
int malloc_struct(t_data **info)
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
int		main(int argc, char **argv, char **envv)
{
	t_data	*info;
	char	*input;
	// int		counter;

	if (argc != 1 || !argv[0])
		return (input_error());
	if (malloc_struct(&info))
		return (1);
	if (copy_envv(&(info->envv), envv))
		return (1);

	handle_sigs_interactive();
	update_env(info);
	int cmd_counter = 0;
	while (1)
	{
		input = readline("minishell🦖>");
		if (!input)
			break ;
		 
		if (input[0] == '\0')
			continue ;	
		add_history(input);
		input = handle_input(info, input, envv);
		if (!input)
			break ;
		free(input);
		free_2d_array(info->env);
		update_env(info);
		exec_stuff(info);
		free_all(info);
		cmd_counter++;
	}
	end_free(input, info);
	return (0);
}
