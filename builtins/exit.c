/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 00:35:13 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/05 19:38:40 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_only_nums(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '+' && str[i + 1]) || (str[i] == '-' && str[i + 1]))
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (-1);
		}
		i++;
	}
	return (1);
}

void	delete_list(t_list **list)
{
	t_list	*temp;
	t_list	*next;

	temp = *list;
	next = NULL;
	while (temp->next != NULL)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	free(temp);
	*list = NULL;
}

void	clear_before_ex(t_data *info, int i)
{
	free_2d_array(info->env);
	if (i == 1)
		delete_list(&info->envv);
	free_all(info);
	free(info);
}

void	exit_program(t_data *info)
{
	int	i;

	i = 0;
	if (!info->cmd[info->index].cmd[i + 1])
	{
		clear_before_ex(info, 1);
		exit(0);
	}
	else if (info->cmd[info->index].cmd[i + 2])
	{
		perror("Too many arguments default exit ran \n");
		info->ret_val = 1;
		exit(1);
	}
	if (info->cmd[info->index].cmd[i + 1])
	{
		if (check_if_only_nums(info->cmd[info->index].cmd[i + 1]) == 1)
		{
			clear_before_ex(info, 1);
			exit(ft_atoi((const char *)info->cmd[info->index].cmd[i + 1]));
		}
		else
		{
			clear_before_ex(info, 1);
			perror("Non numerical arguments");
			exit(1);
		}
	}
}
