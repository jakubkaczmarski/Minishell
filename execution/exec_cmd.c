/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:12:31 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/18 17:12:58 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void	execute_single_command(t_data *info, int index, int forker, int i)
{
	int j;
	j = 0;
	info->command_and_param = command_and_param_from_line(info->cmd_table[index]);
	split_path_to_exec(info,forker, i);
	j = 0;
	while(info->command_and_param[j])
	{
		free(info->command_and_param[j]);
		j++;
	}
}

int split_path_to_exec(t_data *info,  int forker, int index)
{
	char **splitted_path;
	char *full_cmd_path;
	// info->path = get_path(info->env);
	splitted_path = ft_split(info->path, ':');
	if(builtin_handler(info) == 1)
	{

		return 0;
	}
	if(!(full_cmd_path = exec_cmd(info, forker, index, splitted_path)))
	{
        printf("Command not found\n");
		free_exec(splitted_path, full_cmd_path);
		return -1;
    }
	else
    {
		free_exec(splitted_path, full_cmd_path);
        return 0;
    }
}

char *get_path(char **envv)
{
	int i = 0;
	char *line;

	line = NULL;
	while(envv[i])
	{
		if(ft_strncmp(envv[i], "PATH=", 5) == 0)
		{
			line = envv[i];
			line = ft_strtrim(line, "PATH=");
		}
		i++;
	}
	return line;
}

char **command_and_param_from_line(char *line)
{
	char **command_and_param;
	line = ft_strtrim(line, " ");
	command_and_param = ft_split(line, ' ');
	free(line);
	return command_and_param;
}