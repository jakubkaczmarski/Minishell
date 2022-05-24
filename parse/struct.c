/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:59:32 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/24 12:47:15 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
inserts a space at the position that you pass
*/
char *insert_space(char *string, int i)
{
	char *new_string;
	int j;
	
	j = 0;
	new_string = malloc(sizeof(char *) * ft_strlen(string) + 1);
	if (!new_string)
		return (string);
	ft_copy(new_string, string, i + 2);
	new_string[i + 1] = ' ';
	ft_copy(&new_string[i + 2], &string[i + 1], 0);
	return (new_string);
}

void track_redirection(t_cmd *cmd, char *string, char c, int j)
{
	int i;

	i = 0;
	if (string[i + 1] == ' ')
		i = 2;
	while (string[i] != ' ' && string[i] != '\0')
		i++;
	if (c == '<')
	{
		cmd->in[j] = ft_substr(string, 0, i);
		printf("in_red[%d]: %s\n", j, cmd->in[j]);
	}
	else if (c == '>')
	{
		cmd->out[j] = ft_substr(string, 0, i);
		printf("out_red[%d]: %s\n", j, cmd->out[j]);
	}
}

void redirections(t_cmd *cmd, char *string)
{
	int i;
	int in_j;
	int out_j;

	i = 0;
	in_j = 0;
	out_j = 0;
	while (string[i])
	{
		if (string[i] == '<')
		{
			if (string[i + 1] != ' ')
				string = insert_space(string, i);
			track_redirection(cmd, &string[i], '<', in_j++);
		}
		else if (string[i] == '>')
		{
			if (string[i + 1] != ' ')
				string = insert_space(string, i);
			track_redirection(cmd, &string[i], '>', out_j++);
		}
		i++;
	}
}

int cmd_tracker(t_cmd *cmd, char *string)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = ft_strlen(string);
	while (string[i] != ' ')
	{
		if (string[i + 2] == '<' || string[i + 2] == '>')
			i++;
		i++;
	}
	while (string[i + j] != '<' && string[i + j] != '>' \
		&& string[i + j] != '\0' && (i + j) != len)
		j++;
	cmd->cmd = ft_split(ft_substr(string, i, j), ' ');
	i = 0;
	while(cmd->cmd[i])
	{
		printf("cmd: %s\n", cmd->cmd[i++]);
	}
	return (1);
}

// void get_cmd_itself(t_cmd *cmd, char *line)
// {
// 	int	i;

// 	i = 0;
// 	while(line[i] == )
// 	{
		
// 	}
// }
//Realocate mem
char **add_after_string(char **arr, char *new_el)
{
	int i = 0;
	char **temp;
	printf("trying to add %s\n", new_el);
	while(arr[i])
	{
		i++;
	}
	temp = ft_calloc((sizeof(char *)), i + 2);
	i = 0;
	while(arr[i])
	{
		temp[i] = arr[i];
		i++;
	}
	
	temp[i] = new_el;
	free(arr);
	return temp;
}
void    print_2d_array(char    **arr, int fd)
{
    int    i;

    i = 0;
    if (arr)
    {
        while (arr[i] != NULL)
        {
            ft_putstr_fd(arr[i], fd);
            if (arr[i][ft_strlen(arr[i]) - 1] != '\n')
                ft_putchar_fd('\n', fd);
            i++;
        }
    }
}

void    free_2d_array(char    **arr)
{
    int    i;

    i = 0;
    if (arr)
    {
        while (arr[i] != NULL) 
        {
            free(arr[i]);
            i++;
        }
    }
    free(arr);
}
t_cmd *alloc_mem_for_info(void)
{

	t_cmd *cmd;

	// arr
	// arr = malloc (sizeof(char *) * amount of ptr +1);
	// arr[i++] = strdup;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	cmd->out  = ft_calloc(sizeof(char *), 1);
	cmd->in  = ft_calloc(sizeof(char *), 1);
	cmd->cmd  = ft_calloc(sizeof(char *), 1);
	cmd->cmd[0] = NULL;
	cmd->in[0] = NULL;
	cmd->out[0] =  NULL;
	return cmd;
}
void	handle_struct(t_data *info)
{
	print_cmd_table(info->cmd_table);
	int i = 0;
	int j = 0;
	char **temp;
	
	while(info->cmd_table[i])
	{

		
		// printf("%p\n", info->cmd[i]);
		temp = ft_split(info->cmd_table[i], ' ');
		print_2d_array(temp, 1)
;		info->cmd[i] =	*alloc_mem_for_info();
		info->cmd[i + 1] =	*alloc_mem_for_info();
		while(temp[j])
		{
			if(temp[j][0] == '<')
			{
				if ((ft_strlen(temp[j]) < 2))
				{
					//This way just add the next and add redirection in front of it 		
				}
				info->cmd[i].in = add_after_string(info->cmd[i].in, temp[j]);
			}else if(temp[j][0] == '>')
			{
				info->cmd[i].out = add_after_string(info->cmd[i].out, temp[j]);
 			}else{
				info->cmd[i].cmd = add_after_string(info->cmd[i].cmd, temp[j]);
				info->amount_cmd++;
			 }
			j++;
		}
			printf("Printing in\n");
			print_2d_array(info->cmd[i].in, 1);
			printf("\nPrinting cmd\n");

			print_2d_array(info->cmd[i].cmd, 1);
			printf("\nPrinting out\n");
			print_2d_array(info->cmd[i].out, 1);
			i++;
		// while(i)
		// free(temp);
	}

	// ft_split("")
	// int i;
	// int j;
	// int position;
	// t_cmd *cmd;

	// i = 0;
	// j = 0;
	// position = 0;
	// while (info->cmd_table[i])
	// {
	// 	printf("------ROUND %d--------\n", i);
	// 	info->cmd[i] = *(t_cmd*)ft_calloc(sizeof(t_cmd *), 1);
	// 	cmd = &(info->cmd[i]);
	// 	cmd->cmd = ft_calloc(sizeof(char **), 1);
	// 	cmd->in = ft_calloc(sizeof(char **), 1);
	// 	cmd->out = ft_calloc(sizeof(char **), 1);
		
	// 	// get_cmd_itself(&(info->cmd[i]), info->cmd_table[i]);
	// 	redirections(&(info->cmd[i]), info->cmd_table[i]);
	// 	info->amount_cmd += cmd_tracker(&(info->cmd[i]), info->cmd_table[i]);
	// 	printf("amount_cmd: %d\n", info->amount_cmd);	
	// 	i++;
	// }
}
