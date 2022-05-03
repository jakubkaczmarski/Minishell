/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:02:58 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/03 18:19:44 by jkaczmar         ###   ########.fr       */
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
	char	***formated_cmds;
	t_list	*envv;
	t_cmd	*cmd;
	char	*sq_flag;
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
void print_envv(char **envv); //for testing


//Command_formatting :)
void	print_lines(t_data *info, int counter);
void	format_line(t_data *info, int counter);
//quotes.c

char	*handle_quotes(char *input);
char *cut_off_douq(char *input);

//builtins
void	pwd(void);
void	cd(t_data *info, int counter);
void	ft_echo(t_data *info, int counter);
//handler.c
void builtin_handler(t_data *info, int counter);

//cleaning_stuff
void    delete_env_list(t_data *info);
#endif