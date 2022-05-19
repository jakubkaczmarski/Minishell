/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:59:32 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/19 21:27:36 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
inserts a space at the position that you pass
*/
char *insert_space(char *string, int i)
{
	char *new_string;
	int j;
	
	j = 0;
	new_string = malloc(sizeof(char *) * ft_strlen(string) + 1);
	if (!new_string)
		return (string);
	ft_copy(new_string, string, i + 1);
	new_string[i] = ' ';
	ft_copy(&new_string[i + 1], &string[i], 0);
	return (new_string);
}

/*
<something.txt
< something.txt
<<something.txt
go though the string and the first word after the redirect is the filename
for each redirect you have to have one index in the array
if there is <sth then insert a space: < sth
*/
int redirect_input(t_cmd *cmd, char *string)
{
	int	i;
	int	j;
	int	start;
	int	index;

	i = 0;
	j = 0;
	start = 0;
	index = 0;
	while (string[i])
	{
		if (string[i + j] == '<')
		{
			start = i;
			if (string[i++ + (++j)] != ' ' && string[i] != '<')
			 	string = insert_space(string, i);
			while (string[i + j] != ' ')
				j++;
			cmd->in[index] = ft_substr(string, start, j + 1);
			printf("in_redirect[%d]: %s\n", index, cmd->in[index]);
			index++;
		}
		i += j;
		j = 0;
		i++;
	}
	return (i);
}

/*
output
*/
int redirect_output(t_cmd *cmd, char *string)
{
	int	i;
	int	j;
	int	start;
	int	index;

	i = 0;
	j = 0;
	start = 0;
	index = 0;
	while (string[i])
	{
		if (string[i + j] == '>')
		{
			start = i;
			if (string[i++ + j] != ' ' && string[i + 1] != '>')
			 	string = insert_space(string, i++);
			while (string[i + j++] != '\0' && string[i + j] != '>')
				j++;
			cmd->out[index] = ft_substr(string, start, j + 1);
			printf("out_redirect[%d]: %s\n", index, cmd->out[index]);
			index++;
			j--;
		}
		i += j;
		j = 0;
		i++;
	}
	return (j);
}

/*
cmd
*/
int redirect_cmd(t_cmd *cmd, char *string)
{
	int i;
	int position;
	char *tmp;

	i = 0;
	position = 0;
	while (cmd->in[i])
		position += ft_strlen(cmd->in[i++]);
	i = 0;
	while (string[position + i] != '>')
		i++;
	tmp = ft_substr(string, position, i);
	cmd->cmd = ft_split(tmp, ' ');
	i = 0;
	while (cmd->cmd[i])
	{
		printf("cmd[%d]: %s\n", i, cmd->cmd[i]);
		i++;
	}
	return (i);
}

void handle_struct(t_data *info)
{
	int i;
	int j;
	int position;

	i = 0;
	j = 0;
	position = 0;
	info->cmd = ft_calloc(sizeof(t_cmd *), 1);
	info->cmd->in = ft_calloc(sizeof(char **), 1);
	info->cmd->in[0] = ft_calloc(sizeof(char *), 1);
	info->cmd->in[0][0] = '\t';
	info->cmd->out = ft_calloc(sizeof(char **), 1);
	info->cmd->out[0] = ft_calloc(sizeof(char *), 1);
	info->cmd->out[0][0] = '\t';
	info->cmd->cmd = ft_calloc(sizeof(char **),1 );
	while (info->cmd_table[i])
	{
		if (ft_strchr(info->cmd_table[i], '<') == NULL && ft_strchr(info->cmd_table[i], '>') == NULL)
		{
			while(info->cmd_table[i])
			{
				info->cmd->cmd[i] = info->cmd_table[i];
				printf("CMd : %s", info->cmd->cmd[i]);
				i++;
			}
			info->amount_cmd = i;
			printf("Command ammout %d", info->amount_cmd);
			break;
		}
		printf("------ROUND %d--------\n", i);
		info->cmd->in[i] = ft_calloc(sizeof(char *) ,1);
		info->cmd->out[i] = ft_calloc(sizeof(char *) ,1);
		position += redirect_input(&(info->cmd[i]), info->cmd_table[i]);
		redirect_cmd(&(info->cmd[i]), info->cmd_table[i]);
		redirect_output(&(info->cmd[i]), info->cmd_table[i]);
		
		i++;
	}
}