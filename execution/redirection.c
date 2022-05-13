/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:05:59 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/13 13:29:33 by jkaczmar         ###   ########.fr       */
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

int	get_num_to_alloc(t_el_counter *el_count, t_data *info, int index)
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
					return -1;
				}
			}
			num_of_words++;
		}
		len_of_wrd++;
		i++;
	}
	el_count->num_of_wrds = num_of_words;
	el_count->redirect_arr = malloc(num_of_words * sizeof(char *));
	return 1;
}

int alloc_mem_for_words(t_el_counter *el_count, t_data *info, int index)
{
	int i = 0;
	int len_of_wrd = 0;
	int num_of_words = -1;
	num_of_words++;
	while(info->cmd_table[index][i])
	{
		if(info->cmd_table[index][i] == '<' || info->cmd_table[index][i] == '>')
		{
			// printf("Len of word %d \n", len_of_wrd);
			
			if((info->cmd_table[index][i] == '<' && info->cmd_table[index][i + 1] == '<' )|| (info->cmd_table[index][i] == '>' && info->cmd_table[index][i + 1] == '>') )
			{
				i++;
				if((info->cmd_table[index][i] == '<' && info->cmd_table[index][i + 1] == '<' )|| (info->cmd_table[index][i] == '>' && info->cmd_table[index][i + 1] == '>'))
				{
					printf("Input Error to many redirections\n");
					return -1;
				}
			}
			el_count->redirect_arr[num_of_words] = ft_substr(info->cmd_table[index], i - len_of_wrd - 1, len_of_wrd);
			printf("Word %s\n", el_count->redirect_arr[num_of_words]);
			len_of_wrd = 0;
			num_of_words++;
		}
		len_of_wrd++;
		if(!info->cmd_table[index][i + 1])
		{
			el_count->redirect_arr[num_of_words] = ft_substr(info->cmd_table[index], i - len_of_wrd - 1, len_of_wrd + 2);
			printf("Word %s\n", el_count->redirect_arr[num_of_words]);
		}

		i++;
	}
	return 1;
}
int		run_redictions(t_data *info, int index)
{
	t_el_counter el_count;
	if(!(ft_strchr(info->cmd_table[index], '<') || ft_strchr(info->cmd_table[index], '>')))
	{
		printf("Redirections are not in the string 🦖\n");
		return 0;
	}
   		// if(get_num_to_alloc(&el_count, info, index) == 1)
		//    {
		// 	// alloc_mem_for_words(&el_count, info, index);
		// 	// printf("What the shell\n");
		//    }
	// int i = 0;
	// while(el_count.redirect_arr[i])
	// {
	// 	printf("%s\n", el_count.redirect_arr[i]);
	// 	i++;
	// }
	// fT_split("<");
	return 1;
}