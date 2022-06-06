/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:13:45 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/06 23:18:05 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_err(t_data *info)
{
	write (2, "No file to read from", 21);
	info->ret_val = 127;
}

int	get_out(t_data *info, int i, int *out_fd)
{
	*out_fd = open(&info->cmd->out[i][2], O_WRONLY
			| O_CREAT | O_APPEND, 0777);
	if (*out_fd < 0)
	{
		write(2, "No file to read from\n", 22);
		exit(127);
	}
	else
	{
		i++;
		close(*out_fd);
	}
	return (0);
}

int	no_path_handling(t_data *info, int fd, int out_fd)
{
	if (non_fork_buid_ins(info) == 1)
	{
		close(fd);
		close(out_fd);
		return (STDIN_FILENO);
	}
	if (check_for_build_child_build_ins(info) == 0)
	{
		close(fd);
		close(out_fd);
		write(2, "Command is wrong\n", 19);
		info->ret_val = 1;
		return (STDIN_FILENO);
	}
	return (-2);
}

int	non_fork_buid_ins(t_data *info)
{
	if (!ft_strncmp(info->cmd[info->index].cmd[0], "cd", 2))
	{
		cd(info);
		return (1);
	}
	if (!ft_strncmp(info->cmd[info->index].cmd[0], "exit", 4))
	{
		exit_program(info);
		return (1);
	}
	else if (!ft_strncmp(info->cmd[info->index].cmd[0], "export", 6))
	{
		export_handler(info, 0);
		return (1);
	}
	else if (!ft_strncmp(info->cmd[info->index].cmd[0], "unset", 5))
	{
		unset_handler(info, 0);
		return (1);
	}
	else
		return (0);
}

int	check_for_build_child_build_ins(t_data *info)
{
	if (info->cmd[info->index].cmd[0])
	{
		if (!ft_strncmp(info->cmd[info->index].cmd[0], "echo", 4))
			return (1);
		else if (!ft_strncmp(info->cmd[info->index].cmd[0], "$?", 2))
		{
			return (1);
		}
		else if (!ft_strncmp(info->cmd[info->index].cmd[0], "env", 3))
			return (1);
		else if (!ft_strncmp(info->cmd[info->index].cmd[0], "pwd", 3))
			return (1);
	}
	return (0);
}
