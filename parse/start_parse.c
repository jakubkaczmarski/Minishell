/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:08:39 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/06 17:58:45 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_after_string(char **arr, char *new_el)
{
	int		i;
	char	**temp;

	i = 0;
	while (arr[i])
		i++;
	temp = ft_calloc((sizeof(char *)), i + 10);
	i = 0;
	while (arr[i])
	{
		temp[i] = ft_strdup(arr[i]);
		i++;
	}
	temp[i] = ft_strdup(new_el);
	free_2d_array(arr);
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
		while (arr[i])
		{
			if (ft_strlen(arr[i]) > 0)
				free(arr[i]);
			i++;
		}
	}
	free(arr);
}

char	*cmd_exists_inp(char *line, char *cmd)
{
	int		i;
	char	**splitted_path;
	char	*full_cmd_path;

	if (!line)
		return (NULL);
	splitted_path = ft_split(line, ':');
	i = 0;
	while (splitted_path[i])
	{
		full_cmd_path = check_for_cmd_in_path(splitted_path[i],
				cmd);
		if (full_cmd_path)
			return (full_cmd_path);
		i++;
	}
	return (NULL);
}
