/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:02:58 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/04/07 11:33:11 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
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
	t_list	*cmd_table;
	t_list	*envv;
	t_cmd	*cmd;
}				t_data;


//			parse
//input.c
void handle_input(t_data *info, char **envv);



#endif