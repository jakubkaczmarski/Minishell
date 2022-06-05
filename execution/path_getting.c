/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_getting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:35:36 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/05 19:32:46 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*cmd_exists(t_data *info)
{
	int		i;
	char	**splitted_path;
	char	*full_cmd_path;

	i = 0;
	if (!info->cmd[info->index].gen_path)
	{
		return (NULL);
	}
	splitted_path = ft_split(info->cmd[info->index].gen_path, ':');
	i = 0;
	while (splitted_path[i])
	{
		full_cmd_path = check_for_cmd_in_path(splitted_path[i],
				info->cmd[info->index].cmd[0]);
		if (full_cmd_path)
		{
			free_2d_array(splitted_path);
			return (full_cmd_path);
		}
		i++;
	}
	free_2d_array(splitted_path);
	return (NULL);
}

char	*get_path(char **envv)
{
	int		i;
	char	*line;

	i = 0;
	while (envv[i])
	{
		if (ft_strncmp(envv[i], "PATH=", 5) == 0)
		{
			line = envv[i];
			line = ft_strtrim(line, "PATH=");
			return (line);
		}
		i++;
	}
	return (ft_calloc(sizeof(char *), 1));
}

char	*check_for_cmd_in_path(char *path, char *command)
{
	char	*cmd;
	char	*cmd1;

	cmd1 = ft_strjoin(path, "/");
	if (access(command, X_OK) == 0)
	{
		cmd = ft_strjoin("", command);
		free(cmd1);
		return (cmd);
	}
	cmd = ft_strjoin(cmd1, command);
	if (access(cmd, X_OK) == 0)
	{
		free(cmd1);
		return (cmd);
	}
	free(cmd1);
	free(cmd);
	return (NULL);
}
