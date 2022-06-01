/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:59:32 by jtomala           #+#    #+#             */
/*   Updated: 2022/06/01 13:41:48 by jkaczmar         ###   ########.fr       */
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

void	handle_red_t(t_data *info, char **temp, int j, char *joined, int i)
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
		info->cmd[i].out = add_after_string(info->cmd[i].out,
				joined);
	}
}

void	handle_red_p(t_data *info, char **temp, int j, char *joined, int i)
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
}

char	*cmd_exists_inp(char *line, char *cmd)
{
	int		i;
	char	**splitted_path;
	char	*full_cmd_path;
	if(!line)
	{
		return NULL;
	}
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

int	find_if_cmd_exist(char *cmd, t_data *info)
{

	info->index = 0;
	info->cmd[info->index].gen_path = get_path(info->env);
	info->cmd[info->index].command_path = cmd_exists_inp(info->cmd[info->index].gen_path, cmd);
	if (info->cmd[info->index].command_path)
	{
	
		return (1);
	}else if(ft_strncmp(cmd, "cd", 2) == 0)
	{
		return (1);
	}
	else if (!ft_strncmp(cmd, "cd", 2))
	{
		return (1);
	}
	if (!ft_strncmp(cmd, "exit", 4))
	{
		return (1);
	}
	else if (!ft_strncmp(cmd, "export", 6))
	{
		return (1);
	}
	else if (!ft_strncmp(cmd, "unset", 5))
	{
		return (1);
	}
	// free(info->cmd[info->index].gen_path);
	return (0);
	//Check if it's the command if not don't add to the command counter 
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
				if (info->amount_cmd == 0 || (argum == 1 && (find_if_cmd_exist(temp[j],info) == 1)))
					info->amount_cmd++;
				info->cmd[i].cmd = add_after_string(info->cmd[i].cmd, temp[j]);
				argum = 0;
			}
			j++;
		}

		// printf("Command amount %d\n", info->amount_cmd);
		// printf("Printing in\n");
		// print_2d_array(info->cmd[i].in, 1);
		// printf("\nPrinting cmd\n");
		// print_2d_array(info->cmd[i].cmd, 1);
		// printf("\nPrinting out\n");
		// print_2d_array(info->cmd[i].out, 1);
		i++;
	}
	alloc_mem_for_info(&info->cmd[i]);
}
