/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 23:38:39 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/19 20:35:07 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void    fake_here_doc(char *line)
{
    char *magic_word;
    while(1)
    {
        magic_word = readline("> "); 
        if(!magic_word)
            break;
        if(ft_strncmp(line, magic_word, ft_strlen(magic_word)) == 0)
        {
            free(magic_word);
            break;
        }
        free(magic_word);
    }
}
int    real_here_doc(char *line)
{
    char *magic_word;
    int pipe_1[2];
    pipe(pipe_1);
    close(pipe_1[0]);
    while(1)
    {
        magic_word = readline(">"); 
        if(!magic_word)
            break;
        if(ft_strncmp(line, magic_word, ft_strlen(magic_word)) == 0)
        {
            free(magic_word);
            break;
        }
        write(pipe_1[1], magic_word, ft_strlen(magic_word));
        write(pipe_1[1], "\n",1);
        free(magic_word);
    }
    return pipe_1[1];
}
int get_real_one(t_info *info, int i)
{
    int err;
    if(info->t_cmd[info->index].in[i][1] == '<' )
    {
        return real_here_doc(info->t_cmd[info->index].in[i]);
    }else{
        if(access(&info->t_cmd[info->index].in[i][2], F_OK) != 0)
        {
            perror("No file to read from");
            return -1;
        }else{
            err =  open(&info->t_cmd[info->index].in[i][2], O_RDONLY);
            if(err < 0)
                perror("ERROR");
        }
    }
    return err;
}

int get_the_real_one_out(t_info *info, int out_fd, int i)
{
 
    if(out_fd == -1)
    {
        out_fd = STDOUT_FILENO;
    }
    if(info->t_cmd[info->index].out[i] && info->t_cmd[info->index].out[i][1] == '>' )
    {
        out_fd =open(&info->t_cmd->out[i][2], O_WRONLY | O_CREAT | O_APPEND, 0777);
        return out_fd;
    }else
        out_fd =open(&info->t_cmd->out[i][2], O_WRONLY | O_CREAT, 0777 );
        if(out_fd < 0)
        {
            perror("No file to read from");
            return -1;
        }else{
            return out_fd;
        }
    return out_fd;
}
int put_proper_in_fd(t_info *info, int fd)
{
    int i = 0;
    if(fd != STDIN_FILENO && fd > 0)
        close(fd);
    //Loop till the last one
    //<< 
    //< and a space
    while( info->t_cmd[info->index].in[i + 1] != NULL)
    {
        if(info->t_cmd[info->index].in[i][1] == '<' )
        {
            fake_here_doc(info->t_cmd[info->index].in[i]);
        }else{
                if(access(&info->t_cmd->in[i][2], F_OK) != 0)
                {
                    perror("No file to read from");
                }else{
                    i++;
                    continue;
                }
        }
        i++;
    }
    return (get_real_one(info, i));
}
int put_proper_out_fd(t_info *info, int out_fd)
{
    int i = 0;

    //  && info->t_cmd[info->index].out[0]
    while( info->t_cmd[info->index].out[i + 1] != NULL )
    {
        if(info->t_cmd[info->index].out[i][1] == '>' )
        {
            if((out_fd =open(&info->t_cmd->out[i][2], O_WRONLY | O_CREAT | O_APPEND, 0777 )) < 0)
                {
                    perror("No file to read from");
                }else{
                    i++;
                    close(out_fd);
                    continue;
                }
        }else{
                if((out_fd = open(&info->t_cmd->out[i][2], O_WRONLY | O_CREAT, 0777 )) < 0)
                {
                    perror("No file to read from");
                }else{
                    close(out_fd);
                    i++;
                    continue;
                }
        }
        i++;
    }
        write(2, "\n", 1);
   ft_putnbr_fd(i, 2);
   write(2, "\n", 1);
    return (get_the_real_one_out(info, out_fd, i));
}

char *cmd_exists(t_info *info)
{
    int  i;
    char **splitted_path = ft_split( info->t_cmd[info->index].gen_path, ':');
    char *full_cmd_path;
    i = 0;
    while(splitted_path[i])
	{
        full_cmd_path = check_for_cmd_in_path(splitted_path[i],info->t_cmd[info->index].cmd[0]);
        // printf("%s\n",splitted_path[i],info->t_cmd[info->index].cmd[0] );
		if(full_cmd_path)
		{
            printf("Command found  %s \n", info->t_cmd[info->index].cmd[0]);
            return full_cmd_path;
		}
		i++;
	}
    return NULL;
}


// if redirections of any kind always use redirection
// if info index == 0 we want to keep stdin 
// else we use pipe 1 [0]


int child_process_in(t_info *info, int fd, int *pipe_1)
{
    int check;
    printf("child process in pipe [0] == %d\n", pipe_1[0]);
    printf("child process in fd == %d\n", fd);
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
               printf("HEIEIIELDEOEGPOWGPJOW\n");
               if ((check = dup2(pipe_1[0], STDIN_FILENO)) < 0)
            {
                perror("fuck off");
                return (-1);
            }
            return (pipe_1[0]);
           }
       
    return (check);
}
int child_process_out(t_info *info, int out_fd, int *pipe_1)
{
   int check;
   printf("index == %d \n", info->index);
    if (out_fd > 2)
    {
        if ((check = dup2(out_fd, STDOUT_FILENO)) < 0)
            {
                perror("fuck off");
                return (-1);
            }
            close(pipe_1[1]);
       return (out_fd);
    }
    else if (info->index == info->cmd_count - 1)
        return (STDOUT_FILENO);
    else 
           {
               if ((check = dup2(pipe_1[1], STDOUT_FILENO)) < 0)
            {
                perror("fuck off");
                return (-1);
            }
            return (pipe_1[1]);
           }
       
    return (0);
    // int check;
    // printf("Out fd %d Pipe 1 %d\n", out_fd, pipe_1[1]);
    // if(out_fd == -1 || info->index == info->cmd_count - 1)
    // {
    //     //Piping
    //     check = dup2(pipe_1[1], STDOUT_FILENO);

    //     if(check < 0)
    //     {

    //             perror("Problem with pipes");
    //             return -1;   
    //     }
    //     return pipe_1[1];

    // }

    // check = dup2(out_fd, STDOUT_FILENO);

    //     if(check < 0)
    //     {
    //         perror("Redireciton err");
    //         return -1;
    //     }
    //     printf("Hiello\n");
    //     check = close(pipe_1[1]);
    //     if(check < 0)
    //     {
    //          perror("Close");
    //         return -1;
    //     }
    // printf("Out_Fd %d\n",out_fd);
    // return out_fd;
}
void run_child(t_info *info,int  fd,int out_fd,int *pipe_1)
{
    int input;
    int output;
    input = child_process_in(info, fd ,pipe_1);
     printf("Final thingy in %d \n", input);
    usleep(51);
    if(input < 0)
        exit(-1);
    output = child_process_out(info, out_fd, pipe_1);
//   printf("Final thingy v 2 Out_fd  %d\n", out_fd);
    write(2, "Final thingy v 2 Out_fd  ", 26);
    ft_putnbr_fd(output, 2);
    write (2, "\n", 1);
  usleep(50);
    if(output < 0)
        exit(-1);

    execve(info->t_cmd[info->index].command_path, &info->t_cmd[info->index].cmd[0], info->env);
    write (2, "HELLOOOEKOPOFKQPWODKOQPWKDPOQWFPOKQFW\n", 39);
    close(pipe_1[0]);
    close(pipe_1[1]);
}
int fork_and_exec(t_info *info,int fd, int out_fd)
{
    // ft_putnbr_fd(out_fd,1);
    // perror();
    // perror("\n")
    printf("we got here\n");
    if(info || fd || out_fd){}
    int pipe_1[2];
    int kurwa_err;
    int status;
    if(pipe(pipe_1) == -1)
        return -1;
    info->pid = fork();
    if(info->pid == -1)
        return - 1;
    if(info->pid == 0)
        run_child(info, fd, out_fd, pipe_1);
    waitpid(info->pid, &status, 0);
    close(pipe_1[1]);
    if(fd > 2)
    close(fd);
    if(out_fd > 2)
    close(out_fd);
    printf("return of exec loop for next fd == %d\n", pipe_1[0]);
    return pipe_1[0];
}
// int clean_stuff();
int exec_prep_thingys(t_info *info,int fd, int out_fd)
{  

    if(!info->t_cmd[info->index].in[0] && info->index == 0)
        fd = -1;
  
   else  if (info->t_cmd[info->index].in[0])
        if((fd = put_proper_in_fd(info, fd)) < 0)
            return -1;

    if(!info->t_cmd[info->index].out[0] && info->index == 0)
    {
        out_fd = -1;
    }
    else
    {

        if((out_fd = put_proper_out_fd(info, out_fd)) < 0)
        {
            close(fd);
            return -1;
        }
    }
      perror("domdqwkodwqkodqwopk");
    if(!info->t_cmd[info->index].cmd[0])
    {
        close(fd);
        close(out_fd);
        return -1;
    }

    info->t_cmd[info->index].gen_path = get_path(info->env);
    // printf("First %s \n, Second %s", info->t_cmd[info->index].gen_path, info->t_cmd[info->index].cmd[0] );
    if(((info->t_cmd[info->index].command_path = cmd_exists(info))))
        printf("Command %s\n", info->t_cmd[info->index].command_path);
    else{
        close(fd);
        close(out_fd);
        perror("There is no command in the path\n");
    }
    //This and command with paht
    //If there is no command you return and close both of them 
    if(!info->t_cmd[info->index + 1].cmd[0])
        out_fd = STDOUT_FILENO;
    return fork_and_exec(info, fd, out_fd);
}
int exec_stuff(t_info *info)
{
    int fd = STDIN_FILENO;
    info->index = 0;
    while (info->index < info->cmd_count)
    { 
        printf("we got here %d info index \n", info->index);
        fd = exec_prep_thingys(info, fd, STDOUT_FILENO);
        info->index++;
    }
    return 0;
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
    
int main(int argc, char **argv, char **env)
{
    if(argc || argv || env)
    {}
    t_commands cmd[2];
    cmd[0].cmd = ft_split("echo Siemanko", ' ');
    cmd[1].cmd = ft_split("grep a", ' ');
    cmd[0].in = calloc(1, sizeof(char *));
    cmd[1].in = calloc(1, sizeof(char **));
    cmd[0].in[0] = ft_strdup(">>som.txt");
    cmd[0].out= calloc(1, sizeof(char **));
    cmd[1].out= calloc(1, sizeof(char **));
    cmd[0].out[0] = ft_strdup("<<out.txt");
    // cmd[0].out[0] = ft_strdup(">>priviet.c");
    t_info info;
    info.t_cmd = &cmd[0];
    info.env = env;
    info.cmd_count = 2;
    exec_stuff(&info);
    // info.t_cmd = cmd[1];
}
