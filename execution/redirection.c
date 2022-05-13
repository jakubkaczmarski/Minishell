/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:05:59 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/13 12:06:12 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int find_len_first_command(t_data *info, int index)
{
	int x = 0;
	while(info->cmd_table[index][x])
	{
		if(info->cmd_table[index][x] == '<' || info->cmd_table[index][x] == '>')
		{
			return x;
			if(info->cmd_table[index][x + 1] == '<' || info->cmd_table[index][x + 1] == '>')
				return x + 1;
		}
		x++;
	}

	return 0;
}

void	get_num_to_alloc(t_el_counter *el_count, char **info)
{
	int counter;

	ft_bzero(el_count, sizeof(el_count));
	counter = 0;
	while(info[counter])
	{
		if(ft_strncmp(">>", info[counter], 2) == 0 || '>' == info[counter][0])
			el_count->ida_red_in++;
		else if(ft_strncmp("<<", info[counter], 2) == 0 || '<' == info[counter][0])
			el_count->ida_red_out++;
		else
			el_count->n_cmd_flags++;
		counter++;
	}
}

int		run_redictions(t_data *info, int index)
{
	t_el_counter el_count;
	char **splitted_thingy = ft_split(info->cmd_table[index],' ');
	if(!(ft_strchr(info->cmd_table[index], '<') || ft_strchr(info->cmd_table[index], '>')))
	{
		// printf("Redirections are not in the string 🦖\n");
		return 0;
	}
	get_num_to_alloc(&el_count, splitted_thingy);
	// printf("Flags : %d\n", el_count.n_cmd_flags);
	// fT_split("<");
	return 1;
}