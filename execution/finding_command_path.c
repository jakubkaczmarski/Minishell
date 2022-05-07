/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_command_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 10:46:09 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/07 16:34:08 by jkaczmar         ###   ########.fr       */
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
		
	// free(cmd);
	return NULL;
}
//Split path 
// $> echo $PATH
// /bin:/usr/bin:/home/user/.bin
//into smaller chunks
int split_path_to_exec(char *path, char **command_and_params, char **env, char *params)
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
			process_1 = fork();
			if(process_1 == -1)
				perror("Forking failed\n");
			else if(process_1 == 0)
			{
				printf("Command found in %s\n", splitted_path[i]);
				execve(full_cmd_path, command_and_params, env);	
			}else{
				wait(NULL);
			}
			break;
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
void	execute_single_command(char **command_and_param, char *path, t_data *info, char **env)
{
	int j;

	j = 0;
	
	command_and_param = command_and_param_from_line(info->cmd_table[0]);
	printf("Command %s\n", command_and_param[0]);
	printf("Parameter %s\n", command_and_param[1]);
	split_path_to_exec(path, command_and_param, env, command_and_param[1]);
	j = 0;
	while(command_and_param[j])
	{
		free(command_and_param[j]);
		j++;
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
	if(!info->cmd_table[i + 1])
		execute_single_command(command_and_param, path, info, env);
	else{
		printf("Pipe or redirection detected\n");
	}
	
	free(command_and_param);
	free(path);
	
}


//Now piping time