/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:08:41 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/30 13:36:50 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
handles the input given by the user and puts it into a struct
*/
int	copy_envv(t_list **l_envv, char **envv)
{
	t_list	*s;
	t_list	*tmp;
	int		i;

	i = 0;
	if (envv)
	{
		s = ft_lstnew(envv[0]);
		while (envv[i])
		{
			tmp = ft_lstnew(envv[i]);
			ft_lstadd_back(&s, tmp);
			i++;
		}
		*l_envv = s;
		tmp = (*l_envv)->next;
		(*l_envv)->next = (*l_envv)->next->next;
		free(tmp);
		return (0);
	}
	return (1);
}

void	print_envv(t_list **envv, int flag)
{
	t_list	*temp;

	temp = *envv;
	if (!temp)
		return ;
	while (temp != NULL)
	{
		if (flag == 1)
			printf("delcare -x %s\n", temp->content);
		else
			printf("%s\n", temp->content);
		temp = temp->next;
	}
}

int	get_size_of_list(t_list **envv)
{
	t_list	*temp;
	int		counter;

	temp = *envv;
	counter = 0;
	if (!temp)
		return (0);
	while (temp != NULL)
	{
		counter++;
		temp = temp->next;
	}
	return (counter);
}

char	**convert_env_list_to_str(t_list **envv)
{
	int		size;
	char	**env_arr;
	int		i;
	t_list	*temp;

	size = get_size_of_list(envv);
	env_arr = ft_calloc(sizeof(char *), size + 1);
	i = 0;
	temp = *envv;
	while (temp != NULL)
	{
		env_arr[i] = ft_strdup(temp->content);
		temp = temp->next;
		i++;
	}
	return (env_arr);
}

char	**add_env(char **env)
{
	char	**ret;
	int		i;

	i = 0;
	while (env[i])
	{
		i++;
	}
	ret = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (env[i])
	{
		ret[i] = ft_strdup(env[i]);
		i++;
	}
	return (ret);
}
