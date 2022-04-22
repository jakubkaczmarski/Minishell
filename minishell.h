/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:02:58 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/04/22 09:05:11 by jtomala          ###   ########.fr       */
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
void	copy_envv(t_list *l_envv, char **envv);
char	*handle_input(t_data *info, char *input, int counter, char **envv);
char	*check_input(char *input, char **envv);
char	*ft_crop_brackets(char *var);
char	*get_value(char *var, int *counter);
char	*return_envv_val(char **envv, char *str);
char	*modify_input(char *input, char *value, int var_len);
int		ft_copy(char *dst, char *src, int len);
void print_envv(t_list *envv); //for testing

#endif