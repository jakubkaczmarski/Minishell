/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crop_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:35:54 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/06 01:27:13 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	prep_redirection(t_data *info, int index, int i char c)
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
