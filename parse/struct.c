/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:59:32 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/20 13:25:21 by jtomala          ###   ########.fr       */
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
	ft_copy(new_string, string, i + 2);
	new_string[i + 1] = ' ';
	ft_copy(&new_string[i + 2], &string[i + 1], 0);
	return (new_string);
}

void track_redirection(t_cmd *cmd, char *string, char c, int j)
{
	int i;

	i = 0;
	if (string[i + 1] == ' ')
		i = 2;
	while (string[i] != ' ' && string[i] != '\0')
		i++;
	if (c == '<')
	{
		cmd->in[j] = ft_substr(string, 0, i);
		printf("in_red[%d]: %s\n", j, cmd->in[j]);
	}
	else if (c == '>')
	{
		cmd->out[j] = ft_substr(string, 0, i);
		printf("out_red[%d]: %s\n", j, cmd->out[j]);
	}
}

void redirections(t_cmd *cmd, char *string)
{
	int i;
	int in_j;
	int out_j;

	i = 0;
	in_j = 0;
	out_j = 0;
	while (string[i])
	{
		if (string[i] == '<')
		{
			if (string[i + 1] != ' ')
				string = insert_space(string, i);
			track_redirection(cmd, &string[i], '<', in_j++);
		}
		else if (string[i] == '>')
		{
			if (string[i + 1] != ' ')
				string = insert_space(string, i);
			track_redirection(cmd, &string[i], '>', out_j++);
		}
		i++;
	}
}

int cmd_tracker(t_cmd *cmd, char *string)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = ft_strlen(string);
	while (string[i] != ' ')
	{
		if (string[i + 2] == '<' || string[i + 2] == '>')
			i++;
		i++;
	}
	while (string[i + j] != '<' && string[i + j] != '>' \
		&& string[i + j] != '\0' && (i + j) != len)
		j++;
	cmd->cmd = ft_split(ft_substr(string, i, j), ' ');
	i = 0;
	while(cmd->cmd[i])
	{
		printf("cmd: %s\n", cmd->cmd[i++]);
	}
	return (1);
}


void handle_struct(t_data *info)
{
	int i;
	int j;
	int position;
	t_cmd *cmd;

	i = 0;
	j = 0;
	position = 0;
	while (info->cmd_table[i])
	{
		printf("------ROUND %d--------\n", i);
		info->cmd[i] = *(t_cmd*)ft_calloc(sizeof(t_cmd *), 1);
		cmd = &(info->cmd[i]);
		cmd->in = ft_calloc(sizeof(char **), 1);
		cmd->out = ft_calloc(sizeof(char **), 1);
		redirections(&(info->cmd[i]), info->cmd_table[i]);
		info->amount_cmd += cmd_tracker(&(info->cmd[i]), info->cmd_table[i]);
		printf("amount_cmd: %d\n", info->amount_cmd);	
		i++;
	}
}
