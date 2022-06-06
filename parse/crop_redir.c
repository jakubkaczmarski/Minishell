/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crop_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:35:54 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/06 23:26:54 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	prep_redirection(t_data *info, int index, int i, char c)
// {	
// }
int	replace_line(t_data *info, int index, char c)
{
	int		i;
	int		j;
	int		size;
	char	*new_line;

	i = 0;
	j = 0;
	size = ft_strlen(info->cmd_table[index]);
	new_line = ft_calloc(sizeof(char), ft_strlen(info->cmd_table[index]) + 1);
	while (i < size)
	{
		if (info->cmd_table[index][i] && info->cmd_table[index][i] == c)
		{
			new_line[j] = info->cmd_table[index][i];
			j++;
			if (info->cmd_table[index][i + 1] &&
				info->cmd_table[index][i + 1] == c)
			{
				new_line[j] = info->cmd_table[0][i + 1];
				if (info->cmd_table[index][i + 2] &&
					info->cmd_table[index][i + 2] == c)
					return (-1);
				i += 2;
				j++;
				while (info->cmd_table[index][i] &&
						info->cmd_table[index][i] == ' ')
					i++;
			}
			else
			{
				i++;
				while (info->cmd_table[index][i] &&
						info->cmd_table[index][i] == ' ')
					i++;
			}
		}
		else
		{
			new_line[j] = info->cmd_table[index][i];
			j++;
			i++;
		}
	}
	free(info->cmd_table[index]);
	info->cmd_table[index] = new_line;
	return (0);
}

int	crop_redir(t_data *info)
{
	int	i;

	i = 0;
	while (info->cmd_table[i])
	{
		if (replace_line(info, i, '<') == -1)
		{
			return (-1);
		}
		if (replace_line(info, i, '>') == -1)
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

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
