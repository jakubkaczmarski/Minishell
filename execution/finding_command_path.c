/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_command_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 10:46:09 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/07 11:38:47 by jkaczmar         ###   ########.fr       */
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
			printf("Command found in %s\n", splitted_path[i]);
			if((process_1 = fork()) == -1)
				perror("Forking failed\n");
			else if(process_1 == 0)
			{
				execve(full_cmd_path, &params, env);
				wait(&process_1);
			}			
			break;
		}
		free(full_cmd_path);
		printf("%s\n", splitted_path[i]);
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
void manage_exec(t_data *info, char **env)
{

	// char *path = get_path(env);
	if(!info && !env)
	{};
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