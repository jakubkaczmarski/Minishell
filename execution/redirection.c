/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:05:59 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/13 12:50:48 by jkaczmar         ###   ########.fr       */
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

void	get_num_to_alloc(t_el_counter *el_count, t_data *info, int index)
{
    int i = 0;
	int len_of_wrd = 0;
	int num_of_words = 0;
	num_of_words++;
	while(info->cmd_table[index][i])
	{
		if(info->cmd_table[index][i] == '<' || info->cmd_table[index][i] == '>')
		{
			// printf("Len of word %d \n", len_of_wrd);
			len_of_wrd = 0;
			if((info->cmd_table[index][i] == '<' && info->cmd_table[index][i + 1] == '<' )|| (info->cmd_table[index][i] == '>' && info->cmd_table[index][i + 1] == '>') )
			{
				i++;
				if((info->cmd_table[index][i] == '<' && info->cmd_table[index][i + 1] == '<' )|| (info->cmd_table[index][i] == '>' && info->cmd_table[index][i + 1] == '>'))
				{
					printf("Input Error to many redirections\n");
					return ;
				}
			}
			num_of_words++;
		}
		len_of_wrd++;
		i++;
	}
	// printf("Len of word %d \n", len_of_wrd);
	// if(el_count)
	// {}
	// printf("Num of words %d\n", num_of_words);
}

int		run_redictions(t_data *info, int index)
{
	t_el_counter el_count;
	if(!(ft_strchr(info->cmd_table[index], '<') || ft_strchr(info->cmd_table[index], '>')))
	{
		printf("Redirections are not in the string 🦖\n");
		return 0;
	}
   get_num_to_alloc(&el_count, info, index);
	printf("Flags : %d\n", el_count.n_cmd_flags);
	// fT_split("<");
	return 1;
}