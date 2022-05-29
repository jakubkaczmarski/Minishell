/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:29:28 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/29 18:43:18 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

static size_t	ft_countwords(const char *str, char c)
{
	size_t	i;
	size_t	count;
	int		flag_s;
	int		flag_d;

	i = 0;
	count = 0;
	flag_s = 0;
	flag_d = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && flag_d == 0 && flag_s == 0)
			count++;
		while (str[i] && str[i] != c)
		{
			check_quotes(str[i], &flag_s, &flag_d);
			i++;
		}
	}
	return (count);
}

static size_t	ft_wordlen(const char *str, char c)
{
	size_t	i;
	int		flag_s;
	int		flag_d;

	i = 0;
	flag_s = 0;
	flag_d = 0;
	while (str[i] && str[i] != c)
	{
		check_quotes(str[i], &flag_s, &flag_d);
		i++;
		while ((flag_s == 1 || flag_d == 1) && str[i] != '\0')
		{
			check_quotes(str[i], &flag_s, &flag_d);
			i++;
		}
	}
	return (i);
}

static char	**ft_freemem(char **new, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free (new[i]);
		i++;
	}
	free (new);
	return (NULL);
}

static char	**ft_fillwords(char **new, char *str, char c, size_t count)
{
	size_t	words;
	size_t	len;
	int		i;
	int		flag;
	int		len_t;

	i = 0;
	words = 0;
	flag = 0;
	len_t = ft_strlen(str);
	while (words < count)
	{
		while (str[i] && str[i] == c)
			i++;
		len = ft_wordlen(str + i, c);
		new[words] = ft_substr(str, i, len);
		str[len_t] = '\0';
		if (!new[words])
			return (ft_freemem(new, words));
		while (str[i] && str[i] != c)
			i = flag_handler(str, &flag, i);
		words++;
	}
	new[words] = NULL;
	return (new);
}

char	**ft_split(const char *str, char c)
{
	size_t	count;
	char	**new;

	if (!str)
		return (NULL);
	count = ft_countwords(str, c);
	new = ft_calloc(sizeof(*new), (count + 1));
	if (!new)
		return (NULL);
	return (ft_fillwords(new, (char *)str, c, count));
}
