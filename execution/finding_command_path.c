/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_command_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 10:46:09 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/07 13:06:54 by jkaczmar         ###   ########.fr       */
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
	cmd = ft_strjoin(cmd1, command);
	// printf("%s, %d\n",cmd,);
	if(access(cmd, F_OK) == 0)
	{   
		free(cmd1);
		return cmd;
	}
		
	free(cmd1);
	return NULL;
}
//Split path 
// $> echo $PATH
// /bin:/usr/bin:/home/user/.bin
//into smaller chunks
int split_path_to_exec(char *path, char *command, char **env, char *params)
{
	int i = 0;

	char **splitted_path = ft_split(path, ':');
	char *full_cmd_path;
	pid_t process_1;
	full_cmd_path = NULL;
	while(splitted_path[i])
	{
		full_cmd_path = check_for_cmd_in_path(splitted_path[i], command);
		if(full_cmd_path)
		{
			process_1 = fork();
			printf("Command found in %s\n", splitted_path[i]);
			if(process_1 == -1)
				perror("Forking failed\n");
			else if(process_1 == 0)
			{
				execve(full_cmd_path, &params, env);	
				sleep(5);
				wait(&process_1);
			}			
			break;
		}
		free(full_cmd_path);
		// printf("%s\n", splitted_path[i]);
		i++;
	}
	if(!full_cmd_path)
	{
        printf("Command not found\n");
        return -1;
    }
	else
    {
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
	int i = 0;
	// int size = 0;
	line = ft_strtrim(line, " ");
	command_and_param = ft_split(line, ' ');
	while(command_and_param[i])
	{
		if(i > 1)
		{
			command_and_param[1] = ft_strjoin(command_and_param[1], command_and_param[i]);
			free(command_and_param[i]);
		}
		i++;
	}
	free(line);
	return command_and_param;
	// command_and_param = ft_split(line, ' ');
}
void free_all(char **command_and_param)
{
	int i = 0;
	while(command_and_param[i])
	{
		free(command_and_param);
		i++;
	}
}
void manage_exec(t_data *info, char **env)
{
	char	*path = get_path(env);
	char	**command_and_param;
	if(!info && !env)
	{};
	int i = 0;

	command_and_param = malloc(sizeof(char **) * 2);
	while(info->cmd_table[i])
	{	
		if(i > 1)
		{
			printf("Pipes detected\n");
		}
		command_and_param = command_and_param_from_line(info->cmd_table[i]);
		printf("Commadn %s\n", command_and_param[0]);
		printf("Parameter %s\n", command_and_param[1]);
		split_path_to_exec(path, command_and_param[0], env, command_and_param[1]);
		free(command_and_param[0]);
		free(command_and_param[1]);
		// wait()
		// free_all(command_and_param);
		i++;
	}
	free(command_and_param);
	// check_for_cmd_in_path(env, )
	// split_path_to_exec(path, info->cmd_table[0], env, "");
	// printf("%s\n", info->cmd_table[0]);
}







// char **get_env_arr(t_data *info, char **env)
// {
// 	char **env_arr = NULL;
// 	// char *line = NULL;
// 	if(info)
// 	{}
// 	// char *temp_line;
// 	// write(1, "dqwdqwdwq",10);
// 	print_envv(info->envv);
// 	ft_putstr_fd(info->envv->content, 1);
// 	// while(info->envv->next)
// 	// {
// 	// 	temp_line = line;
// 	// 	line = ft_strjoin(temp_line, info->envv->content);
// 	// 	// line = ft_strjoin(line, "\n");
// 	// 	free(temp_line);
// 	// 	info->envv = info->envv->next;
// 	// }
// 	// if(info->envv->content)
// 	// {
// 	// 	temp_line = line;
// 	// 	line = ft_strjoin(temp_line, info->envv->content);
// 	// 	line = ft_strjoin(line, "\n");
// 	// 	free(temp_line);
// 	// 	info->envv = info->envv->next;
// 	// }
// 	// env_arr = ft_split(line, '\n');
// 	return env_arr;
// }