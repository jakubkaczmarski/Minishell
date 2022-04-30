/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@students.42wolfsburg.de>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:02:58 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/04/30 08:12:27 by jtomala          ###   ########.fr       */
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
char	*handle_input(t_data *info, char *input, char **envv);
char	*check_input(char *input, char **envv);
char	*find_dollar(char *input);
int		count_dollars(char *input);
void print_envv(char **envv); //for testing

//input_utils.c
int		ft_copy(char *dst, char *src, int len);
char	*modify_input(char *input, char *value, int var_len);
char	*return_envv_val(char **envv, char *str);
char	*ft_crop_brackets(char *var);
char	*get_value(char *var, int *counter);

//quotes.c
char *quote_handler(char *input);
char *cut_off_douq(char *input);

//envv.c
int	copy_envv(t_list *l_envv, char **envv);

//cmd_table.c
char *cmd_table_handler(t_data *info, char *input);
int count_pipes(char *input);
char *remove_spaces_at_pipes(char *input);


//			builtins
//handler.c
void builtin_handler(t_data *info);

#endif