/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:07:31 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/18 00:48:21 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_echo(char *input)
{
	int flag;
	int i;
	char **str;

	flag = 0;
	i = 1;
	//echo -n -n-n-n-n-n bla bla bla
	str = ft_split(input, ' ');
	if(!str[1])
	{
		printf("\n");
		return ;
	}
	//if str[1] == -n set flag to 1
	if (!ft_strncmp(str[1], "-n", 2))
	{
		flag = 1;
		i++;
	}
	while (str[i])
		printf("%s ", str[i++]);
	if (flag == 0)
		printf("\n");
}