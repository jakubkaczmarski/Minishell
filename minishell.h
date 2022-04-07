/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:02:58 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/04/07 14:45:42 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <readline/readline.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>



//for each command
typedef struct s_cmd {
	char	*name;
	int amount_of_args;
}				t_cmd;


//main-struct
typedef struct s_data {
	char	**cmd_table;
	t_list	*envv;
	t_cmd	*cmd;
}				t_data;


//			parse
//input.c
void handle_input(t_data **info, char *input, int counter);
void copy_envv(t_data **info, char **envv);
void handle_input(t_data **info, char *input, int counter);
void check_input(t_data *info, char *input);
char *exchange_envv(t_data *info, char *str);

#endif