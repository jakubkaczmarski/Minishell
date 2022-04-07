/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:43:07 by jtomala           #+#    #+#             */
/*   Updated: 2021/12/02 11:03:06 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	if (!s || n == 0)
		return (NULL);
	while (i < n)
	{
		if (*(char *)(s + i) == (char) c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
