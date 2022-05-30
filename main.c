/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:08:54 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/30 17:56:28 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		input_error()
{
	printf("Input Error\n");
	return (1);
}

void	free_all(t_data *info, int counter)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < info->amount_cmd)
	{
		// while (info->cmd[i].cmd[j])
		// {
		// 	free(info->cmd[i].cmd[j]);
		// 	j++;
		// }
		// j = 0;
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
		// free(info->cmd[i].command_path);
		// free(info->cmd[i].gen_path);
		i++;
	}
	while (info->cmd_table[counter])
		free(info->cmd_table[counter++]);
}

void	update_env(t_data *info)
{
	char	**str;

	str = convert_env_list_to_str(&info->envv);
	// int i = 0;
	info->env = add_env(str);
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
	*info = malloc(sizeof(t_data *));
	(*info)->envv = malloc(sizeof(t_list *));
	if (!*info || !(*info)->envv)
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
	int		counter;

	//info = NULL;
	if (argc != 1 || !argv[0])
		return (input_error());
	if (malloc_struct(&info))
		return (1);
	if (copy_envv(&(info->envv), envv))
		return (1);
	handle_sigs_interactive(); // signal
	while (1)
	{
		input = readline("minishell🦖>");
		if (!input)
			break ;
		if (input[0] == '\0')
			continue ;
		update_env(info); 
		add_history(input);
		input = handle_input(info, input, envv);
		if (!input)
			break ;
		
		exec_stuff(info);
		printf("Ret value %d\n", info->ret_val );
		free(input);
		counter = 0;
		free_all(info, counter);
	}
	end_free(input, info);
	return (0);
}
