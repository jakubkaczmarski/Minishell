/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 23:38:39 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/03 23:46:55 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

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

int	fork_and_exec(t_data *info, int fd, int out_fd)
{
	int	pipe_1[2];
	int	status;

	if (pipe(pipe_1) == -1)
		return (-1);
	info->pid = fork();
	if (info->pid == -1)
		return (-1);
	if (info->pid == 0)
		run_child(info, fd, out_fd, pipe_1);
	waitpid(info->pid, &status, 0);
	info->ret_val = status;
	if (status > 255)
		info->ret_val = status / 256;
	// handle_child_signals();
	close(pipe_1[1]);
	if (fd > 2)
		close(fd);
	if (out_fd > 2)
		close(out_fd);
	return (pipe_1[0]);
}

int	prep_manag(t_data *info, int *fd, int *out_fd)
{
	if (!info->cmd[info->index].in[0] && info->index == 0)
		*fd = -1;
	else if (info->cmd[info->index].in[0])
	{
		*fd = put_proper_in_fd(info, *fd);
		if (*fd < 0)
			return (-1);
		else if(*fd == 127)
			return (-1);
	}
	if (!info->cmd[info->index].out[0] && info->index == 0)
		*out_fd = -1;
	else if (info->cmd[info->index].out[0])
	{
		*out_fd = put_proper_out_fd(info, *out_fd);
		if (*out_fd < 0)
		{
			close(*fd);
			return (-1);
		}else if(*out_fd == 127)
			return (-1);
	}
	return (0);
}
int	check_for_build_child_build_ins(t_data *info)
{
	if (info->cmd[info->index].cmd[0])
	{
		if (!ft_strncmp(info->cmd[info->index].cmd[0], "echo", 4))
			return (1);
		else if (!ft_strncmp(info->cmd[info->index].cmd[0], "$?", 2))
			return (1);
		else if (!ft_strncmp(info->cmd[info->index].cmd[0], "env", 3))
			return (1);
		else if (!ft_strncmp(info->cmd[info->index].cmd[0], "pwd", 3))
			return (1);
	}
		return (0);
}
int	exec_prep_thingys(t_data *info, int fd, int out_fd)
{
	if (prep_manag(info, &fd, &out_fd) != 0)
		return (-1);
	if (!info->cmd[info->index].cmd[0])
	{
		close(fd);
		close(out_fd);
		return (-1);
	}

	info->cmd[info->index].gen_path = get_path(info->env);
	info->cmd[info->index].command_path = cmd_exists(info);
	free(info->cmd[info->index].gen_path);
	if (!info->cmd[info->index].command_path)
	{
		if (non_fork_buid_ins(info) == 1)
			return (STDIN_FILENO);
		if(check_for_build_child_build_ins(info) == 0)
		{
			close(fd);
			close(out_fd);
			write(2, "Command is wrong\n", 19);
			info->ret_val = 1;
			return (STDIN_FILENO);
		}
	}else if(ft_strncmp(info->cmd[info->index].cmd[0], "cd", 2) == 0)
	{
		cd(info);
		close(fd);
		close(out_fd);
		info->ret_val = 1;
		return (1);
	}

	return (fork_and_exec(info, fd, out_fd));
}

int	exec_stuff(t_data *info)
{
	int	fd;

	fd = STDIN_FILENO;
	info->index = 0;
	if(info->amount_cmd == 0 && info->cmd[info->index].in[0])
	{
		if (info->cmd[info->index].in[0][1] == '<')
			fake_here_doc(&info->cmd[info->index].in[0][2]);
		else
		{
			if (access(&info->cmd->in[0][2], F_OK) != 0)
			{
				info->ret_val = 127;
				write(2, "No file to read from\n", 21);
			}
		}
	}
	while (info->index < info->amount_cmd)
	{
		fd = exec_prep_thingys(info, fd, STDOUT_FILENO);
		// if(info->command_and_param)
			// free(info->command_and_param);
		info->index++;
	}
	return (0);
}
