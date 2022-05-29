/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:41:00 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/29 14:41:42 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		put_proper_in_fd(t_data *info, int fd)
{
	int	i;

	i = 0;
	if (!fd)
	{
	}
	// printf("File_fd in put proper in fd %d\n", fd);
	if (fd != STDIN_FILENO && fd > 0)
		close(fd);
	while (info->cmd[info->index].in[i + 1])
	{
		if (info->cmd[info->index].in[i][1] == '<')
		{
			fake_here_doc(info->cmd[info->index].in[i]);
		}
		else
		{
			if (access(&info->cmd->in[i][2], F_OK) != 0)
			{
				write(2, "No file to read from", 21);
			}
			else
			{
				i++;
				continue ;
			}
		}
		i++;
	}
	return (get_real_one(info, i));
}

int		put_proper_out_fd(t_data *info, int out_fd)
{
	int	i;

	i = 0;
	while (info->cmd[info->index].out[i + 1] != NULL)
	{
		if (info->cmd[info->index].out[i][1] == '>')
		{
			if ((out_fd = open(&info->cmd->out[i][2],
								O_WRONLY | O_CREAT | O_APPEND,
								0777)) < 0)
			{
				write(2, "No file to read from", 21);
				exit(1);
			}
			else
			{
				i++;
				close(out_fd);
				continue ;
			}
		}
		else
		{
			if ((out_fd =
						open(&info->cmd->out[i][2], O_WRONLY | O_CREAT, 0777)) < 0)
			{
				write(2, "No file to read from", 21);
				exit(1);
			}
			else
			{
				close(out_fd);
				i++;
				continue ;
			}
		}
		i++;
	}
	//         write(2, "\n", 1);
	//    ft_putnbr_fd(i, 2);
	//    write(2, "\n", 1);
	return (get_the_real_one_out(info, out_fd, i));
}

int		child_process_in(t_data *info, int fd, int *pipe_1)
{
	int	check;

	if (fd > 2)
	{
		if ((check = dup2(fd, STDIN_FILENO)) < 0)
		{
			perror("fuck off");
			return (-1);
		}
		close(pipe_1[0]);
		return (fd);
	}
	else if (info->index == 0)
		return (STDIN_FILENO);
	else
	{
		if ((check = dup2(pipe_1[0], STDIN_FILENO)) < 0)
		{
			exit(1);
		}
		return (pipe_1[0]);
	}
	return (check);
}

int		child_process_out(t_data *info, int out_fd, int *pipe_1)
{
	int	check;

	if (out_fd > 2)
	{
		if ((check = dup2(out_fd, STDOUT_FILENO)) < 0)
		{
			perror("out Error");
			return (-1);
		}
		close(pipe_1[1]);
		return (out_fd);
	}
	else if (info->index == info->amount_cmd - 1)
		return (STDOUT_FILENO);
	else
	{
		if ((check = dup2(pipe_1[1], STDOUT_FILENO)) < 0)
		{
			perror("Out error");
			return (-1);
		}
		return (pipe_1[1]);
	}
	return (0);
}

void	run_child(t_data *info, int fd, int out_fd, int *pipe_1)
{
	int	input;
	int	output;
	int	stat;

	input = child_process_in(info, fd, pipe_1);
	usleep(51);
	if (input < 0)
		exit(-1);
	output = child_process_out(info, out_fd, pipe_1);
	usleep(50);
	if (output < 0)
		exit(-1);
	stat = builtin_handler(info) == 1;
	if (stat == 1)
	{
		close(pipe_1[0]);
		close(pipe_1[1]);
		exit(-1);
	}
	else if (stat == 2)
	{
	}
	else
	{
		// perror("Exec of cmd\n");
		// printf("Command Path %s\n", info->cmd[info->index].command_path);
		// printf("Command %s\n",  info->cmd[info->index].cmd[0]);
		execve(info->cmd[info->index].command_path,
				info->cmd[info->index].cmd,
				info->env);
	}
	close(pipe_1[0]);
	close(pipe_1[1]);
	exit(-1);
}
