/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:12:30 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/04/06 21:46:36 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Find one word in the string thingy
int	get_to_actual_charac(int *starting_index, char *str)
{
	if(!str[*starting_index])
	{
		printf("NULL");
		return 1;
	}
	while(str[*starting_index])
	{
		if(str[*starting_index] == ' ' || str[*starting_index] == '\t')
			*starting_index = *starting_index + 1;
		else
			break;
	}
	return 0;
}
char *find_cmd(int *starting_index, char *str)
{
	//Find the command itself
	int w_size;
	int i;
	int first_size;
	first_size = *starting_index;
	w_size = 0;
	i = 0;
	if(get_to_actual_charac(starting_index, str) == 1)
		return NULL;
	while(str[*starting_index])
	{
		if(str[*starting_index] != ' ' && str[*starting_index] != '\t')
			w_size++;
		else
			break;
		*starting_index = *starting_index + 1;
	}
	if(w_size == 0)
		return NULL;
	*starting_index -= w_size;
	char *cmd = malloc(sizeof(char) * (w_size + 1));
	
	while(str[*starting_index] && *starting_index < w_size + first_size + 1)
	{

		cmd[i++] = str[*starting_index];
		*starting_index = *starting_index + 1;
	}
	cmd[i + 1] = '\0';
	return cmd;
}

int main(void)
{
	int starting_index = 0;
	char *wrd;
	int i = 0;
	char str[] = {"echo witam pozdrawiam z rodzinka"};
	while(1)
	{
		wrd = find_cmd(&starting_index,str);
		if(!wrd)
			break;
		i++;
	}
	printf("%d", i);
}