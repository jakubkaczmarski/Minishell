/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:02:58 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/12 10:24:24 by jtomala          ###   ########.fr       */
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

//main.c
int	input_error();
void print_envv(t_list *envv, int flag);

//			parse
//input.c
char	*handle_input(t_data *info, char *input, char **envv);
char	*check_input(char *input, char **envv);
char	*find_dollar(char *input);
int		count_dollars(char *input);

//input_utils.c
int		ft_copy(char *dst, char *src, int len);
char	*modify_input(char *input, char *value, int var_len);
char	*return_envv_val(char **envv, char *str);
char	*ft_crop_brackets(char *var);
char	*get_value(char *var, int *counter);

//quotes.c
char	*quote_handler(char *input);
char	*cut_off_douq(char *input);

//envv.c
int		copy_envv(t_list **l_envv, char **envv);

//cmd_table.c
void	print_cmd_table(char **cmd_table); //for testing
char	*remove_spaces(char *input, int x, int i);
char	*remove_spaces_at_pipes(char *input);
char	*remove_multi_spaces(char *input, int i, int j);
char 	*cmd_table_handler(t_data *info, char *input);

//cmd_table_utils.c
int		count_pipes(char *input);
int		count_multis(char *input);

//			builtins
//handler.c
void	builtin_handler(t_data *info);

//export.c
void	export_handler(t_data *info, int index);
void	export_in_envv(t_list **envv, char *var_val);
int		ft_strint(char *str, char c);
int		ft_isvalid(char *str);

//unset.c
void	unset_handler(t_data *info, int index);
void	remove_in_envv(t_list **envv, char *var);
int		replace_value_in_env(char **var_val, char *var, t_list *tmp, t_list *curr);

//echo.c
void ft_echo(char *input);

#endif