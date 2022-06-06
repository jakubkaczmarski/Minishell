/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:59:32 by jtomala           #+#    #+#             */
/*   Updated: 2022/06/06 17:58:37 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*alloc_mem_for_info(t_cmd *cmd)
{
	cmd->out = ft_calloc(sizeof(char *), 5);
	cmd->in = ft_calloc(sizeof(char *), 5);
	cmd->cmd = ft_calloc(sizeof(char *), 5);
	return (cmd);
}

void	handle_red_t(t_data *info, char **temp, t_container *container)
{
	if (temp[container->j][1] && temp[container->j][1] == '>')
	{
		info->cmd[container->i].out
			= add_after_string(info->cmd[container->i].out, temp[container->j]);
	}
	else
	{
		temp[container->j][0] = ' ';
		container->line = ft_strjoin(">", temp[container->j]);
		info->cmd[container->i].out
			= add_after_string(info->cmd[container->i].out, container->line);
		free(container->line);
	}
}

void	handle_red_p(t_data *info, char **temp, t_container *container)
{
	if (temp[container->j][1] && temp[container->j][1] == '<')
	{
		info->cmd[container->i].in
			= add_after_string(info->cmd[container->i].in, temp[container->j]);
	}
	else
	{
		temp[container->j][0] = ' ';
		container->line = ft_strjoin("<", temp[container->j]);
		info->cmd[container->i].in
			= add_after_string(info->cmd[container->i].in, container->line);
		free(container->line);
	}
}

int	find_if_cmd_exist(char *cmd, t_data *info, int index)
{
	info->index = 0;
	if (info->cmd[index].command_path)
		free(info->cmd[index].command_path);
	info->cmd[index].gen_path = get_path(info->env);
	info->cmd[index].command_path
		= cmd_exists_inp(info->cmd[index].gen_path, cmd);
	free(info->cmd[index].gen_path);
	if (info->cmd[index].command_path)
	{
		free(info->cmd[index].command_path);
		return (1);
	}
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (!ft_strncmp(cmd, "cd", 2))
		return (1);
	if (!ft_strncmp(cmd, "exit", 4))
		return (1);
	else if (!ft_strncmp(cmd, "export", 6))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (1);
	return (0);
}

void	handle_struct(t_data *info)
{
	char				**temp;
	int					argum;
	t_container			container;

	container.line = NULL;
	container.i = 0;
	container.j = 0;
	info->amount_cmd = 0;
	argum = 0;
	info->cmd = ft_calloc(sizeof(t_cmd), 30);
	while (info->cmd_table[container.i])
	{
		temp = ft_split(info->cmd_table[container.i], ' ');
		alloc_mem_for_info(&info->cmd[container.i]);
		argum = 1;
		container.j = 0;
		while (temp[container.j])
		{
			if (temp[container.j][0] == '<')
			{
				handle_red_p(info, temp, &container);
				argum = 1;
			}
			else if (temp[container.j][0] == '>')
			{
				handle_red_t(info, temp, &container);
				argum = 1;
			}
			else
			{
				if (info->amount_cmd == 0
					|| ((argum == 1)
						&& (find_if_cmd_exist(temp[container.j], info, container.i) == 1)))
					info->amount_cmd++;
				info->cmd[container.i].cmd = add_after_string(
						info->cmd[container.i].cmd, temp[container.j]);
				argum = 0;
			}
			container.j ++;
		}
		free_2d_array(temp);
		container.i++;
	}
	alloc_mem_for_info(&info->cmd[container.i]);
}

// ft_putstr_fd("Printing array thingy\n", 1);
// print_2d_array(info->cmd[0].cmd, 1);
// if(temp)
// {
// 	print_2d_array(temp, 2);
// 	free_2d_array(temp);
// }
// 		printf("Command amount %d\n", info->amount_cmd);
// printf("Printing in\n");
// print_2d_array(info->cmd[i].in, 1);
// printf("\nPrinting cmd\n");
// print_2d_array(info->cmd[i].cmd, 1);
// printf("\nPrinting out\n");
// print_2d_array(info->cmd[i].out, 1);
