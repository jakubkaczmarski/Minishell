/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:46:34 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/16 15:24:32 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_cmd(t_el_counter *counter)
{
	int i = 0;
	while(counter->cmd_arr[i].command)
	{
		if(counter->cmd_arr[i].flag[0] == 'N')
		{
			return counter->cmd_arr[i].command;
		}
		i++;
	}
	return NULL;
}
int		exec_cmd_and_close_fds(t_el_counter *el_counter, char  **env)
{
	char **command_and_param = ft_split(get_cmd(el_counter), ' ');
	char	*path = get_path(env);
	t_data info;
	info.cmd_table = malloc(sizeof(char **) * 1);
	info.cmd_table[0] = get_cmd(el_counter);
	if(!command_and_param)
	{
		printf("There is no command to exec\n");
		close(el_counter->fd_input);
		close(el_counter->fd_output);
		return -1;
	}
	if(el_counter->fd_input != -1)
	{
		execute_single_command(command_and_param, path, &info , env, 0,el_counter->fd_input, 0);
		close(el_counter->fd_input);
		waitpid(el_counter->fd_input, NULL, 0);
	}
	if(el_counter->fd_output != 0)
	{
		if(el_counter->fd_output != -1)
		{	
			execute_single_command(command_and_param, path, &info, env, 0, el_counter->fd_output, 1);
			close(el_counter->fd_output);
			waitpid(el_counter->fd_output, NULL, 0);
		}
	}
	if(el_counter){}
	return 0;
}

int		run_redictions(t_data *info, int index, char **env)
{
	t_el_counter el_counter;
	el_counter.red_num_in = 0;
	el_counter.red_num_out = 0;
	if(!(ft_strchr(info->cmd_table[index], '<') || ft_strchr(info->cmd_table[index], '>')))
	{
		printf("Redirections are not in the string 🦖\n");
		return 0;
	}
	Kurwa(&el_counter, info->cmd_table[index]);
	loop_through_redir(&el_counter);
	if((el_counter.fd_input = exec_input_red(&el_counter)) == -1)
	{
		// printf("No input redirections found\n");
	};
	if((el_counter.fd_output = exec_output_red(&el_counter)) == -1)
	{
		printf("No file found in directory\n");
	}
	if(env)
	{}
	exec_cmd_and_close_fds(&el_counter, env);
	int i = 0;
	while(i < el_counter.num_of_wrds - 1 )
	{
		// printf("Flag : %s \t Command %s \n", el_counter.cmd_arr[i].flag, el_counter.cmd_arr[i].command);
		free(el_counter.redirect_arr[i]);
		i++;
	}
	free(el_counter.redirect_arr);

	return 1;
}
//First get the case when i need to run heredoc
//Then get the word that ends the heredoc save it into the t_el_counter structure
//Then i can run this command thingy
//And i can just run it before executing the command in the output in the if statement
//
int get_here_doc(t_el_counter *el_counter)
{
	int		here_fd;
	char	*inp;
	if(el_counter)
	{}
	if(access("czary_mary_dzikie_weze", F_OK))
	{
		here_fd = open("czary_mary_dzikie_weze", O_CREAT | O_RDWR, 0666);
	}else
		here_fd = open("czary_mary_dzikie_weze", O_WRONLY | O_TRUNC, 0666);
	if(here_fd == -1)
	{
		close(here_fd);
		perror("Here_doc not created\n");
		return (-1);
	}
	while(1)
	{
		inp = readline(">");
		if(!inp)
		{
			printf("Here document delimited by end of file (we need this delimiter)\n");
			return -1;
		}
		
		if(ft_memcmp(el_counter->magic_here_doc_word, inp, ft_strlen(el_counter->magic_here_doc_word) + 1))
		{
			int i = 0;
			i = ft_strlen(inp);
			write(here_fd, inp, i);
			write(here_fd, "\n", i);
		}else{
			close(here_fd);
			return 0;
		}
		// ft_memcmp(
	}
	
	return -1;
}