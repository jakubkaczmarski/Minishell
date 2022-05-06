/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@students.42wolfsburg.de>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:43:50 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/06 15:34:51 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
'export' is 7 characters long so look after that for the 
variable and store it. The variable ends at the equal sign 
so after that comes the value, store it as well
*/
void export_handler(t_data *info, int index)
{
	int i;
	int j;
	char *var;
	char *value;

	i = 0;
	j = 0;
	//variabl part
	while (info->cmd_table[index][i + 7] != '=')
		i++;
	var = ft_substr(info->cmd_table[index], 7, i);
	printf("var: %s and %i\n", var, i);

	//value part
	while (info->cmd_table[index][i + 8 + j] != '\0')
		j++;
	value = ft_substr(info->cmd_table[index], i + 8, j);
	printf("value: %s and %i\n", value, j);
}