/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 23:38:39 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/29 01:49:05 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int non_fork_buid_ins(t_data *info)
{
    int	y;

	y = 0;
     if (!ft_strncmp(info->cmd[info->index].cmd[0], "cd", 2))
	{	
        cd(info);
		return (1);
	}
     if (!ft_strncmp(info->cmd[info->index].cmd[0], "exit", 4))
	{
        exit_program(info);
		return (1);
	}else if (!ft_strncmp(info->cmd[info->index].cmd[0], "export", 6))
	{
		export_handler(info, y);
		info->ret_val = 0;
		return (1);
	}
	else if (!ft_strncmp(info->cmd[info->index].cmd[0], "unset", 5))
	{
		unset_handler(info, y);
		info->ret_val = 0;
		return (1);
	}else{
        return (0);
    }
}
int fork_and_exec(t_data *info,int fd, int out_fd)
{
    if(info || fd || out_fd){}
    int pipe_1[2];
    int status;
    if(pipe(pipe_1) == -1)
        return -1;
    info->pid = fork();
    if(info->pid == -1)
        return - 1;
    if(info->pid == 0)
        run_child(info, fd, out_fd, pipe_1);
    waitpid(info->pid, &status, 0);
    handle_child_signals();
    close(pipe_1[1]);
    if(fd > 2)
    close(fd);
    if(out_fd > 2)
    close(out_fd);
    return pipe_1[0];
}

int exec_prep_thingys(t_data *info,int fd, int out_fd)
{  
    if(!info->cmd[info->index].in[0] && info->index == 0)
        fd = -1;
   else if(info->cmd[info->index].in[0])
        if((fd = put_proper_in_fd(info, fd)) < 0)
            return -1;
    if(!info->cmd[info->index].out[0] && info->index == 0)
        out_fd = -1;
    else if(info->cmd[info->index].out[0])
    {
        if((out_fd = put_proper_out_fd(info, out_fd)) < 0)
        {
            close(fd);
            return -1;
        }
    }

    if(!info->cmd[info->index].cmd[0])
    {
        close(fd);
        close(out_fd);
        return -1;
    }
    info->cmd[info->index].gen_path = get_path(info->env);
    if((!(info->cmd[info->index].command_path = cmd_exists(info))))
    {
        if(non_fork_buid_ins(info) == 1)
            return STDIN_FILENO;
        else{
            close(fd);
            close(out_fd);
            write(2,"Command is wrong\n",19);
            return STDIN_FILENO;
        }
    }
    return fork_and_exec(info, fd, out_fd);
}
int exec_stuff(t_data *info)
{

    int fd = STDIN_FILENO;
    info->index = 0;

    while (info->index < info->amount_cmd)
    { 
        fd = exec_prep_thingys(info, fd, STDOUT_FILENO);
        info->index++;
    }
    return 0;
}
