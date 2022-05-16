#include "../minishell.h"

char	*get_wrd(char *trimmed_line, int *i)
{
	if(trimmed_line[*i])
	{
		if(trimmed_line[*i] == '<' || trimmed_line[*i] == '>')
		{
			*i = *i + 1;
			if((trimmed_line[*i] == '<' && trimmed_line[*i + 1] == '<') || (trimmed_line[*i + 1] == '>' && trimmed_line[*i] == '>'))
			{
				*i = *i + 1;
			}
			
		}
	}
	while(trimmed_line[*i])
	{
		if(trimmed_line[*i + 1] == '<' || trimmed_line[*i + 1] == '>' || !trimmed_line[*i + 1])
		{
			*i = *i + 1;
			return ft_substr(trimmed_line, 0,*i);
		}
		*i = *i + 1;
	}
	return NULL;
}
int Kurwa(t_el_counter *kurwa, char *line)
{
	int i = 0;
	char *trimmed_line;
	trimmed_line = ft_strtrim(line, " ");
	int index = 0;
	char *wrd = get_wrd(trimmed_line, &index);
	i++;
	char *temp;
	if(kurwa){}
	while(wrd)
	{
		free(wrd);
		temp = trimmed_line;
		trimmed_line = ft_substr(trimmed_line, index, ft_strlen(trimmed_line) - index);
		index = 0;
		free(temp);
		wrd = get_wrd(trimmed_line, &index);
		i++;
	}
	if(wrd)
	{}
	if(i == 0)
		return 0;
	kurwa->redirect_arr = malloc(sizeof(char**) * (i));
	kurwa->num_of_wrds = i;
	i = 0;
	index = 0;
	trimmed_line = ft_strtrim(line, " ");

	kurwa->redirect_arr[i] = get_wrd(trimmed_line, &index);
	i++;

	while(i < kurwa->num_of_wrds  )
	{
		temp = trimmed_line;
		trimmed_line = ft_substr(trimmed_line, index, ft_strlen(trimmed_line) - index);
		index = 0;
		free(temp);
		kurwa->redirect_arr[i] = get_wrd(trimmed_line, &index);
		i++;
	}
	return 0;
}

int		loop_through_redir(t_el_counter *el_counter)
{
	int i = 0;
	el_counter->cmd_arr = malloc(sizeof(t_cmd) * el_counter->num_of_wrds);
	while(el_counter->redirect_arr[i])
	{
		if(el_counter->redirect_arr[i][0] == '<')
		{
			if(el_counter->redirect_arr[i][1] == '<')
			{
				el_counter->cmd_arr[i].command = &el_counter->redirect_arr[i][2];
				el_counter->cmd_arr[i].flag = calloc(2, sizeof(char));
				el_counter->cmd_arr[i].flag = "<<";
				el_counter->red_num_out++;
			}else
			{
				el_counter->cmd_arr[i].command = &el_counter->redirect_arr[i][1];
				el_counter->cmd_arr[i].flag = calloc(2, sizeof(char));
				el_counter->cmd_arr[i].flag = "<";
				el_counter->red_num_out++;
			}
		}else if(el_counter->redirect_arr[i][0] == '>')
		{
			if(el_counter->redirect_arr[i][1] == '>')
			{
				el_counter->cmd_arr[i].command = &el_counter->redirect_arr[i][2];
				el_counter->cmd_arr[i].flag = calloc(2, sizeof(char));
				el_counter->cmd_arr[i].flag = ">>";
				el_counter->red_num_in++;
			}else
			{
				el_counter->cmd_arr[i].command = &el_counter->redirect_arr[i][1];
				el_counter->cmd_arr[i].flag = calloc(2, sizeof(char));
				el_counter->cmd_arr[i].flag = ">";
				el_counter->red_num_in++;
			}
		}else{
			el_counter->cmd_arr[i].command = el_counter->redirect_arr[i];
			el_counter->cmd_arr[i].flag = calloc(sizeof(char), 2);
			el_counter->cmd_arr[i].flag[0] = 'N';
			el_counter->num_of_cmds++;
		}
		i++;
	}
	return 0;
}
int	exec_input_red(t_el_counter *el_counter)
{
	int i = 0;
	int in_num = el_counter->red_num_in;
	int fd;
	while(i < el_counter->num_of_wrds - 1)
	{
		if(el_counter->cmd_arr[i].flag[1] == '>')
		{
			if(access(el_counter->cmd_arr[i].command,W_OK) == 0)
			{
				fd = open(el_counter->cmd_arr[i].command, O_APPEND | O_RDWR, 0777);
			}else
			{
				fd = open(el_counter->cmd_arr[i].command, O_CREAT | O_RDWR, 0777);
			}
			in_num--;
			if(in_num == 0)
			{
				return fd;
			}
		}
		else if(el_counter->cmd_arr[i].flag[0] == '>' && el_counter->red_num_in++)
		{
			fd = open(el_counter->cmd_arr[i].command, O_CREAT | O_RDWR, 0777);
			in_num--;
			if(in_num == 0)
			{
				return fd;
			}else{
				close(fd);
			}
		}
		
		i++;
	}
	return -1;
}
int	exec_output_red(t_el_counter *el_counter)
{
	int i = 0;
	int	fd;
	int out_num = el_counter->red_num_out;
	while(i < el_counter->num_of_wrds - 1)
	{
		if(el_counter->cmd_arr[i].flag[1] == '<')
		{
			if(access(el_counter->cmd_arr[i].command,W_OK) == 0)
			{
				fd = open(el_counter->cmd_arr[i].command, O_RDWR , 0777);
			}else
			{
				return -1;
			}
			out_num--;
			if(out_num == 0)
			{
				return fd;
			}
		}
		else if(el_counter->cmd_arr[i].flag[0] == '<' && el_counter->red_num_out++)
		{	
			if(access(el_counter->cmd_arr[i].command,W_OK) == 0)
			{
				fd = open(el_counter->cmd_arr[i].command, O_RDWR , 0777);
			}else{
				return -1;
			}
			out_num--;
			if(out_num == 0)
			{
				// printf("Last in %s Command thingy\n", el_counter->cmd_arr[i].command);
				return fd;
			}else{
				close(fd);
			}
		}
		i++;
	}
	return 0;
}
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
		printf("No input redirections found\n");
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

