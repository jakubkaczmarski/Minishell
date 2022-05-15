/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_command_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 10:46:09 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/15 19:47:44 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Take fragment of path as a parameter append command to it and check if it's there
//For us to execute :)
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
	// printf("%s, %d\n",cmd,);
	if(access(cmd, F_OK) == 0)
	{
		free(cmd1);
		return cmd;
	}
	free(cmd1);
	free(cmd);
	return NULL;
}
//Split path 
// $> echo $PATH
// /bin:/usr/bin:/home/user/.bin
//into smaller chunks
int split_path_to_exec(char *path, char **command_and_params, char **env, char *params, int forker)
{
	int i = 0;
	char **splitted_path = ft_split(path, ':');
	char *full_cmd_path;
	pid_t process_1;
	if(!params)
	{}
	full_cmd_path = NULL;
	while(splitted_path[i])
	{
		full_cmd_path = check_for_cmd_in_path(splitted_path[i], command_and_params[0]);
		if(full_cmd_path)
		{
			if(forker == 1)
			{
				execve(full_cmd_path, command_and_params, env);
				break;
			}else
			{
				process_1 = fork();
				if(process_1 == -1)
					perror("Forking failed\n");
				else if(process_1 == 0)
				{
					if(forker != 0)
						dup2(forker,  STDOUT_FILENO);
					execve(full_cmd_path, command_and_params, env);
				}
				else
					wait(NULL);
				break;
			}
			
		}
		i++;
	}
	i = 0;
	if(!full_cmd_path)
	{
        printf("Command not found\n");
		free(full_cmd_path);
		while(splitted_path[i])
		{
			free(splitted_path[i]);
			i++;
		}
		free(splitted_path);
        return -1;
    }
	else
    {
		while(splitted_path[i])
		{
			free(splitted_path[i]);
			i++;
		}
		free(splitted_path);
		free(full_cmd_path);
        return 0;
    }
}

//Get PATH to check
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
void	execute_single_command(char **command_and_param, char *path, t_data *info, char **env, int index, int forker)
{
	int j;

	j = 0;
	
	command_and_param = command_and_param_from_line(info->cmd_table[index]);
	// printf("Command %s\n", command_and_param[0]);
	// printf("Parameter %s\n", command_and_param[1]);
	split_path_to_exec(path, command_and_param, env, command_and_param[1], forker);
	j = 0;
	while(command_and_param[j])
	{
		free(command_and_param[j]);
		j++;
	}
}
int look_for_redirections(t_data *info, int counter)
{
	char *cmd = info->cmd_table[counter];
	if(!cmd)
	{}
	return 0;
	// while(dpdpdw)
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
	//We need to iterate through string and find << or  <
	//I have to find if there are << or >> or < or > between two commands
	//the easiest solution would be to run ft_split for all of those
	// while(info->cmd_table[i])
	// {
	// 	info->cmd_table[i] != 
	// }
}
void manage_exec(t_data *info, char **env)
{
	char	*path = get_path(env);
	char	**command_and_param;
	if(!info && !env)
	{};
	int i = 0;
	command_and_param = malloc(sizeof(char **) * 2);
	// int num_of_red = look_for_redirections();
	while(info->cmd_table[i])
	{
		// info->cmd_table[i] 
	
		if(!info->cmd_table[i + 1])
		{
			if(run_redictions(info, i,env) != 0)
			{
			}else
				execute_single_command(command_and_param, path, info, env, 0, 0);
			i++;
		}
		else{
			if(run_redictions(info, i, env) != 0)
			{
				run_redictions(info, i + 1, env);
			}else
				piping(command_and_param, path, info, env, i);
			i += 2;
		}
	}
	free(command_and_param);
	free(path);
}

//Now piping time
int piping(char **command_and_param, char *path, t_data *info, char **env, int index)
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
		execute_single_command(command_and_param, path, info, env, index, 1);
	}
	pid2 = fork();
	if(pid2 < 0)
		return -1;
	if(pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute_single_command(command_and_param, path, info, env, index + 1, 1);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return 0;
}
// int	format_in_redir(t_data *info, int counter)
// {
	
// }
