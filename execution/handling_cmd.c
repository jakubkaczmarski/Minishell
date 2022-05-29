/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:13:45 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/29 18:32:51 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_err(void)
{
	write (2, "No file to read from", 21);
	exit (1);
}

int	get_out(t_data *info, int i, int *out_fd)
{
	*out_fd = open(&info->cmd->out[i][2], O_WRONLY
			| O_CREAT | O_APPEND, 0777);
	if (*out_fd < 0)
	{
		write(2, "No file to read from", 21);
		exit(1);
	}
	else
	{
		i++;
		close(*out_fd);
	}
	return (0);
}
