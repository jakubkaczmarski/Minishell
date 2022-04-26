/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:17:52 by jtomala           #+#    #+#             */
/*   Updated: 2022/04/25 14:02:33 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c && ((s[i - 1] != '\'') \
			|| (s[i - 1] == '\'' && s[i - 2] == '"')))
			return (&((char *)s)[i]);
		i++;
	}
	if (!c && s[i] == '\0')
		return ((char *) s + i);
	return (NULL);
}
