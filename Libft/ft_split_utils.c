/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:06:49 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/06 10:08:46 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	check_quotes(char str, int *flag_s, int *flag_d)
{
	if (str == '\'' && *flag_s == 0)
		*flag_s = 1;
	else if (str == '\'' && *flag_s == 1)
		*flag_s = 0;
	else if (str == '"' && *flag_d == 0)
		*flag_d = 1;
	else if (str == '"' && *flag_d == 1)
		*flag_d = 0;
}

int	flag_handler(const char *str, int *flag, int i)
{
	check_quotes(str[i], flag, flag);
	i++;
	while (*flag == 1)
		check_quotes(str[i++], flag, flag);
	return (i);
}
