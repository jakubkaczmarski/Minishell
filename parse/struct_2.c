/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@students.42wolfsburg.de>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:54:09 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/31 09:07:11 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
inserts a space at the position that you pass
*/
char	*insert_space(char *string, int i)
{
	char	*new_string;

	new_string = malloc(sizeof(char *) * ft_strlen(string) + 1);
	if (!new_string)
		return (string);
	ft_copy(new_string, string, i + 2);
	new_string[i + 1] = ' ';
	ft_copy(&new_string[i + 2], &string[i + 1], 0);
	return (new_string);
}

void	track_redirection(t_cmd *cmd, char *string, char c, int j)
{
	int	i;

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

void	redirections(t_cmd *cmd, char *string)
{
	int	i;
	int	in_j;
	int	out_j;

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

int	cmd_tracker(t_cmd *cmd, char *string)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(string);
	while (string[i] != ' ')
	{
		if (string[i + 2] == '<' || string[i + 2] == '>')
			i++;
		i++;
	}
	while (string[i + j] != '<' && string[i + j] != '>'
		&& string[i + j] != '\0' && (i + j) != len)
		j++;
	printf("is it here\n");
	cmd->cmd = ft_split(ft_substr(string, i, j), ' ');
	i = 0;
	return (1);
}
