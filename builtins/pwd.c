/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:52:56 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/07 16:11:21 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_path(void)
{
	char	*buff;
	int		counter;

	counter = 10;
	buff = malloc(counter * sizeof(char));
	getcwd(buff, counter);
	while (errno == ERANGE)
	{
		errno = 0;
		counter += 10;
		free(buff);
		buff = malloc(counter * sizeof(char));
		getcwd(buff, counter);
	}
	printf("%s\n", buff);
	free(buff);
}
