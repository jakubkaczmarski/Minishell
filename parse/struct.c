/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:59:32 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/29 19:54:40 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_after_string(char **arr, char *new_el)
{
	int		i;
	char	**temp;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	temp = ft_calloc((sizeof(char *)), i + 2);
	i = 0;
	while (arr[i])
	{
		temp[i] = arr[i];
		i++;
	}
	temp[i] = new_el;
	free(arr);
	return (temp);
}

void	print_2d_array(char **arr, int fd)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i] != NULL)
		{
			ft_putstr_fd(arr[i], fd);
			if (arr[i][ft_strlen(arr[i]) - 1] != '\n')
				ft_putchar_fd('\n', fd);
			i++;
		}
	}
}

void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i] != NULL)
		{
			free(arr[i]);
			i++;
		}
	}
	free(arr);
}

t_cmd	*alloc_mem_for_info(t_cmd *cmd)
{
	cmd->out = ft_calloc(sizeof(char *), 2);
	cmd->in = ft_calloc(sizeof(char *), 2);
	cmd->cmd = ft_calloc(sizeof(char *), 2);
	cmd->cmd[0] = NULL;
	cmd->in[0] = NULL;
	cmd->out[0] = NULL;
	cmd->cmd[1] = NULL;
	cmd->in[1] = NULL;
	cmd->out[1] = NULL;
	return (cmd);
}

void	handle_struct(t_data *info)
{
	int		i;
	int		j;
	char	**temp;
	char	*joined;
	int		argum;

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
				if (temp[j][1] && temp[j][1] == '<')
				{
					info->cmd[i].in = add_after_string(info->cmd[i].in,
							temp[j]);
				}
				else
				{
					temp[j][0] = ' ';
					joined = ft_strjoin("<", temp[j]);
					info->cmd[i].in = add_after_string(info->cmd[i].in, joined);
				}
				argum = 1;
			}
			else if (temp[j][0] == '>')
			{
				if (temp[j][1] && temp[j][1] == '>')
				{
					info->cmd[i].out = add_after_string(info->cmd[i].out,
							temp[j]);
				}
				else
				{
					temp[j][0] = ' ';
					joined = ft_strjoin(">", temp[j]);
					printf("Joined %s\n", joined);
					info->cmd[i].out = add_after_string(info->cmd[i].out,
							joined);
				}
				argum = 1;
			}
			else
			{
				if (argum == 1 || info->amount_cmd == 0)
					info->amount_cmd++;
				info->cmd[i].cmd = add_after_string(info->cmd[i].cmd, temp[j]);
				argum = 0;
			}
			j++;
		}
		i++;
	}
	alloc_mem_for_info(&info->cmd[i]);
}

	// printf("Command amount %d\n", info->amount_cmd);
		// printf("Printing in\n");
		// print_2d_array(info->cmd[i].in, 1);
		// printf("\nPrinting cmd\n");
		// print_2d_array(info->cmd[i].cmd, 1);
		// printf("\nPrinting out\n");
		// print_2d_array(info->cmd[i].out, 1);