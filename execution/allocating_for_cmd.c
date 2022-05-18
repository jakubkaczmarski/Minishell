/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocating_for_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:45:59 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/17 23:56:20 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
int		manage_here_doc(t_el_counter *el_counter, int index)
{
    char **magic_word = ft_split(el_counter->cmd_arr[index].command, ' ');
    el_counter->magic_here_doc_word = magic_word[0];
    if(get_here_doc(el_counter) == 0)
    {
        int here_fd = open("czary_mary_dzikie_weze", O_CREAT | O_RDWR, 0666);
        unlink("czary_mary_dzikie_weze");
        return here_fd;
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
                fd = manage_here_doc(el_counter, i);
				return fd;
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
				return fd;
			}else{
				close(fd);
			}
		}
		i++;
	}
	return 0;
}