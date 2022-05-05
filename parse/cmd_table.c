/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@students.42wolfsburg.de>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 08:09:29 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/02 09:15:31 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
removes the spaces around the pipe
*/
char    *remove_spaces_at_pipes(char *input)
{
    int x;
    int i;
    char *new_str;

    x = 0;
    i = 0;
    while (input[x])
    {
        if (input[x] == '|' && (input[x - 1] == ' ' || input[x + 1] == ' '))
        {
            new_str = ft_calloc(sizeof(char *), ft_strlen(input));
            if (input[x - 1] == ' ')
                i = ft_copy(new_str, input, x);
            else
                i = ft_copy(new_str, input, x + 1);
            i += ft_copy(&new_str[i], &input[x], 2);
            if (input[x + 1] == ' ')
                ft_copy(&new_str[i], &input[x + 2], 0);
            else
                ft_copy(&new_str[i], &input[x + 1], 0);
            free(input);
            return (new_str);
        }
        x++;
    }
    return (input);
}

/*
counts all the pipes that have a space before and/or after a pipe
*/
int count_pipes(char *input)
{
    int i;
    int amount_pipes;

    i = 0;
    amount_pipes = 0;
    while (input[i])
    {
        if (input[i] == '|' && (input[i - 1] == ' ' || input[i + 1] == ' '))
            amount_pipes++;
        i++;
    }
    return (amount_pipes);
}

/*
[testfunction] prints out the command table
*/
void print_cmd_table(char **cmd_table)
{
    int i;

    i = 0;
    while (cmd_table[i])
    {
        printf("[%d] %s\n", i, cmd_table[i]);
        i++;
    }
}

/*
if somewhere is more then one space in a row
remove all additional
*/
char *remove_multi_spaces(char *input)
{
    int i;
    int j;
    int counter;
    char *new_input;

    i = 0;
    j = 0;
    counter = 0;
    new_input = ft_calloc(sizeof(char *), ft_strlen(input) + 1);
    if (!new_input)
        return (input);
    while (input[i])
    {
        if (input[i] == ' ' && input[i + 1] == ' ')
        {
            while (input[i + counter] == ' ')
                counter++;
            j = ft_copy(new_input, input, i + 2);
            ft_copy(&new_input[j], &input[i + counter], 0);
            i += counter;
            counter = 0;
        }
        i++;
    }
    if (j == 0)
        return (input);
    free(input);
    return (new_input);
}

/*
counts how many multi spaces are in the string
*/
int count_multis(char *input)
{
    int counter;
    int i;

    counter = 0;
    i = 0;
    while (input[i])
    {
        if (input[i] == ' ' && input[i + 1] == ' ')
        {
            while (input[i] == ' ')
                i++;
            counter++;
        }
        i++;
    }
    return (counter);
}

/*
takes the input in puts it into the cmd_table. 
before that, it removes the spaces around the pipe
and then splits the input by pipe.
*/
char *cmd_table_handler(t_data *info, char *input)
{
    int amount_pipes;
    int amount_multis;

    amount_pipes = count_pipes(input);
    amount_multis = count_multis(input);
    while (amount_pipes-- > 0)
        input = remove_spaces_at_pipes(input);
    while (amount_multis-- > 0)
        input = remove_multi_spaces(input);
    info->cmd_table = ft_split(input, '|');
    print_cmd_table(info->cmd_table);
    return (input);
}