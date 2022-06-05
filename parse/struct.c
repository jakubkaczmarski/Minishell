/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:59:32 by jtomala           #+#    #+#             */
/*   Updated: 2022/06/06 01:24:55 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*alloc_mem_for_info(t_cmd *cmd)
{
	cmd->out = ft_calloc(sizeof(char **), 5);
	cmd->in = ft_calloc(sizeof(char **), 5);
	cmd->cmd = ft_calloc(sizeof(char **), 5);
	return (cmd);
}

void	handle_red_t(t_data *info, char **temp, int j, char *joined, int i)
{
	if (temp[j][1] && temp[j][1] == '>')
	{
		info->cmd[i].out = add_after_string(info->cmd[i].out, temp[j]);
	}
	else
	{
		temp[j][0] = ' ';
		joined = ft_strjoin(">", temp[j]);
		info->cmd[i].out = add_after_string(info->cmd[i].out, joined);
		free(joined);
	}
}

void	handle_red_p(t_data *info, char **temp, int j, char *joined, int i)
{
	if (temp[j][1] && temp[j][1] == '<')
	{
		info->cmd[i].in = add_after_string(info->cmd[i].in, temp[j]);
	}
	else
	{
		temp[j][0] = ' ';
		joined = ft_strjoin("<", temp[j]);
		info->cmd[i].in = add_after_string(info->cmd[i].in, joined);
		free(joined);
	}
}

int	find_if_cmd_exist(char *cmd, t_data *info)
{
	info->index = 0;
	if (info->cmd[info->index].command_path)
		free(info->cmd[info->index].command_path);
	info->cmd[info->index].gen_path = get_path(info->env);
	info->cmd[info->index].command_path
		= cmd_exists_inp(info->cmd[info->index].gen_path, cmd);
	free(info->cmd[info->index].gen_path);
	if (info->cmd[info->index].command_path)
	{
		free(info->cmd[info->index].command_path);
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
	int		i;
	int		j;
	char	**temp;
	char	*joined;
	int		argum;

	joined = NULL;
	i = 0;
	j = 0;
	info->amount_cmd = 0;
	argum = 0;
	info->cmd = ft_calloc(sizeof(t_cmd *), 30);
	while (info->cmd_table[i])
	{
		temp = ft_split(info->cmd_table[i], ' ');
		alloc_mem_for_info(&info->cmd[i]);
		argum = 1;
		j = 0;
		while (temp[j])
		{
			if (temp[j][0] == '<')
			{
				handle_red_p(info, temp, j, joined, i);
				argum = 1;
			}
			else if (temp[j][0] == '>')
			{
				handle_red_t(info, temp, j, joined, i);
				argum = 1;
			}
			else
			{
				if (info->amount_cmd == 0
					|| (argum == 1 && (find_if_cmd_exist(temp[j], info) == 1)))
					info->amount_cmd++;
				info->cmd[i].cmd = add_after_string(info->cmd[i].cmd, temp[j]);
				argum = 0;
			}
			j++;
		}
		free_2d_array(temp);
// 		printf("Command amount %d\n", info->amount_cmd);
// printf("Printing in\n");
// print_2d_array(info->cmd[i].in, 1);
// printf("\nPrinting cmd\n");
// print_2d_array(info->cmd[i].cmd, 1);
// printf("\nPrinting out\n");
// print_2d_array(info->cmd[i].out, 1);
		i++;
	}
	// ft_putstr_fd("Printing array thingy\n", 1);
	// print_2d_array(info->cmd[0].cmd, 1);
	alloc_mem_for_info(&info->cmd[i]);
}

// if(temp)
// {
// 	print_2d_array(temp, 2);
// 	free_2d_array(temp);
// }
