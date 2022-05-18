/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_command_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 10:46:09 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/18 14:09:59 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *check_for_cmd_in_path(char *path, char *command)
{
	char *cmd;
	char *cmd1;
	cmd1 = ft_strjoin(path, "/");
	if(access(command, F_OK) == 0)
	{
		cmd = ft_strjoin("", command);
		return cmd;
	}
	cmd = ft_strjoin(cmd1, command);
	if(access(cmd, F_OK) == 0)
	{
		free(cmd1);
		return cmd;
	}
	free(cmd1);
	free(cmd);
	return NULL;
}

char	*exec_cmd(t_data *info, int forker, int index, char **splitted_path)
{
	char *full_cmd_path;
	int i = 0;
	pid_t process_1;

	while(splitted_path[i])
	{
		full_cmd_path = check_for_cmd_in_path(splitted_path[i], info->command_and_param[0]);
		if(full_cmd_path)
		{
			if(forker == 1)
			{
				execve(full_cmd_path, info->command_and_param, info->env);
				break;
			}else
			{
				process_1 = fork();
				if(process_1 == -1)
					perror("Forking failed\n");
				else if(process_1 == 0)
				{
					if(forker != 0 && index == 1)
						dup2(forker, STDIN_FILENO);
					else if(forker != 0)
						dup2(forker,  STDOUT_FILENO);
					execve(full_cmd_path, info->command_and_param, info->env);
				}
				else
					wait(NULL);
				break;
			}
		}
		i++;
	}
	return full_cmd_path;
}
int		free_exec(char **splitted_path, char *full_cmd_path)
{
	int i;

	i = 0;
	free(full_cmd_path);
	while(splitted_path[i])
	{
		free(splitted_path[i]);
		i++;
	}
	free(splitted_path);
    return -1;
}
//into smaller chunks
int split_path_to_exec(t_data *info,  int forker, int index)
{
	char **splitted_path;
	char *full_cmd_path;

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
int check_for_redirections(char *str)
{
	int i = 0;
	char **arr_str = NULL;
	char *ptr;
	while(ft_strnstr(str, "<", ft_strlen(str)) || ft_strnstr(str, ">", ft_strlen(str)))
	{
		if((ptr = ft_strnstr(str, "<", ft_strlen(str))) != NULL)
		{
			*ptr = ' ';
			arr_str = ft_split(str,'<');
		}else if((ptr = ft_strnstr(str, ">", ft_strlen(str))) != NULL )
		{
			*ptr = ' ';
			arr_str = ft_split(str,'>');
		}
	}	
	if(!arr_str)
	{
		return 0;
	}
	else{
		while(arr_str[i])
		{
			printf("%s", arr_str[i]);
			i++;
		}
	}
	return 1;
}

int	check_if_only_red(char *cmd)
{
	int	i = 0;
	while(cmd[i])
	{
		if(cmd[i] != '<' && cmd[i] != '>')
		{
			return 0;
		}
		i++;
	}
	return 1;
}

void manage_exec(t_data *info, char **env)
{
	info->path = get_path(env);
	if(!info && !env)
	{};
	int i = 0;
	int err;
	info->command_and_param = malloc(sizeof(char **) * 2);
	while(info->cmd_table[i])
	{
		if(check_if_only_red(info->cmd_table[i]) == 1)
			return ;
		if(!info->cmd_table[i + 1])
		{
			if(run_redictions(info, i,env) != 0)
			{
			}else
				execute_single_command(info, 0, 0, -1);
			i++;
		}
		else{
			if((err = run_redictions(info, i, env)) != 0)
			{
				run_redictions(info, i + 1, env);
				
			}else if(err == 1)
				piping(info, i);
			i += 2;
		}
	}
	free(info->command_and_param);
	free(info->path);
}

int piping( t_data *info, int index)
{
	int fd[2];
	int pid2;
	if ((pipe(fd)) == -1)
		return -1;
	int pid1 = fork();
	if(pid1 < 0)
		return -1;
	if(pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute_single_command( info, index, 1, -1);
	}
	pid2 = fork();
	if(pid2 < 0)
		return -1;
	if(pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute_single_command(info, index + 1, 1, -1);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return 0;
}