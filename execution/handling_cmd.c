/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:13:45 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/18 17:16:02 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		exec_cmd_and_close_fds(t_el_counter *el_counter, char  **env)
{
	char **command_and_param = ft_split(get_cmd(el_counter), ' ');
	t_data info;
	info.path = get_path(env);
	info.cmd_table = malloc(sizeof(char **) * 1);
	info.cmd_table[0] = get_cmd(el_counter);
	info.env = env;
	if(!command_and_param)
	{
		printf("There is no command to exec\n");
		close(el_counter->fd_input);
		close(el_counter->fd_output);
		return -1;
	}
	if(el_counter->fd_input != -1)
	{
		execute_single_command(&info , 0,el_counter->fd_input, 0);
		close(el_counter->fd_input);
		waitpid(el_counter->fd_input, NULL, 0);
	}
	if(el_counter->fd_output != 0)
	{
		if(el_counter->fd_output != -1)
		{	
			execute_single_command( &info, 0, el_counter->fd_output, 1);
			close(el_counter->fd_output);
			waitpid(el_counter->fd_output, NULL, 0);
		}
	}
	if(el_counter){}
	return 0;
}