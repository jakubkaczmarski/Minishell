/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:46:34 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/31 17:09:01 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fake_here_doc(char *line)
{
	char	*magic_word;

	handle_here_doc_sig_par();
	while (1)
	{
		magic_word = readline("> ");
		if (!magic_word)
			break;
		if (magic_word[0] && ft_strncmp(line, magic_word, ft_strlen(magic_word)) == 0)
		{
			if(magic_word)
				free(magic_word);
			break ;
		}
		free(magic_word);
	}
}

int	real_here_doc(char *line)
{
	char	*magic_word;
	int		pipe_1[2];

	pipe(pipe_1);
	handle_here_doc_sig_par();
	while (1)
	{
		magic_word = readline(">");
		if (!magic_word)
		{
			break;
		}
		if (magic_word[0] &&ft_strncmp(line, magic_word, ft_strlen(magic_word)) == 0)
		{
			if(magic_word)
				free(magic_word);
			break ;
		}
		write(pipe_1[1], magic_word, ft_strlen(magic_word));
		write(pipe_1[1], "\n", 1);
		free(magic_word);
	}
	close(pipe_1[1]);
	return (pipe_1[0]);
}

int	get_real_one(t_data *info, int i)
{
	int	err;

	if (info->cmd[info->index].in[i][1] == '<')
	{
		return (real_here_doc(&info->cmd[info->index].in[i][2]));
	}
	else
	{
		if (access(&info->cmd[info->index].in[i][2], F_OK) != 0)
		{
			perror("No file to read from");
			return (-1);
		}
		else
		{
			err = open(&info->cmd[info->index].in[i][2], O_RDONLY);
			if (err < 0)
				perror("ERROR");
		}
	}
	return (err);
}

int	get_the_real_one_out(t_data *info, int out_fd, int i)
{
	if (out_fd == -1)
	{
		out_fd = STDOUT_FILENO;
	}
	if (info->cmd[info->index].out[i]
		&& info->cmd[info->index].out[i][1] == '>')
	{
		out_fd = open(&info->cmd->out[i][2], O_WRONLY
				| O_CREAT | O_APPEND, 0777);
		return (out_fd);
	}
	else
		out_fd = open(&info->cmd->out[i][2], O_WRONLY | O_CREAT, 0777);
	if (out_fd < 0)
	{
		write(2, "No file to read from", 21);
		return (-1);
	}
	else
	{
		return (out_fd);
	}
	return (out_fd);
}
