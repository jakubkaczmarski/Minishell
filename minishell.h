/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtomala <jtomala@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:02:58 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/07 16:11:02 by jtomala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>

typedef struct s_cmd
{
	char		**in;
	char		**out;
	char		**cmd;
	char		*command_path;
	char		*gen_path;
}				t_cmd;

typedef struct s_container
{
	int			i;
	int			j;
	int			index;
	char		*line;
}				t_container;

// main-struct
typedef struct s_data
{
	char		**cmd_table;
	t_list		*envv;
	t_cmd		*cmd;
	int			amount_cmd;
	char		*path;
	int			index;
	int			pid;
	int			forker;
	char		**env;
	char		**command_and_param;
	int			ret_val;
	int			size;
}				t_data;

typedef struct s_count_el
{
	char		**redirect_arr;
	t_cmd		*cmd_arr;
	int			red_num_in;
	int			red_num_out;
	int			n_cmd_flags;
	int			num_of_wrds;
	int			num_of_cmds;
	int			ida_cmd_flags;
	int			fd_input;
	int			fd_output;
	int			here_doc_thingy;
	char		*magic_here_doc_word;
}				t_el_counter;

// main.c
int				input_error(void);
void			print_envv(t_list **envv, int flag);

//			parse
// input.c
char			*handle_input(t_data *info, char *input);
char			*check_input(char *input, t_list *envv);
char			*find_dollar(char *input);
int				count_dollars(char *input);
void			delete_list(t_list **list);
// input_utils.c
int				ft_copy(char *dst, char *src, int len);
char			*modify_input(char *input, char *value, int var_len);
char			*return_envv_val(t_list *envv, char *str);
char			*ft_crop_brackets(char *var);
char			*get_value(char *var, int *counter);
int				replace_line(t_data *info, int index, char c);
int				crop_redir(t_data *info);
// struct.c
void			handle_struct(t_data *info);

// quotes.c
char			*quote_handler(char *input);
char			*cut_off_quotes(char *input, int quote);

// envv.c
int				copy_envv(t_list **l_envv, char **envv);

// cmd_table.c
void			print_cmd_table(char **cmd_table); // for testing
char			*remove_spaces(char *input, int x, int i);
char			*remove_spaces_at_pipes(char *input);
char			*remove_multi_spaces(char *input, int i, int j);
char			*cmd_table_handler(t_data *info, char *input);

// cmd_table_utils.c
int				count_pipes(char *input);
int				count_multis(char *input);
int				flag_check(char *input, int counter);
int				flag_check_single(char *input, int counter);

//			builtins
// execution_handler.c
int				builtin_handler(t_data *info);

// export.c
int				ft_isvalid(char *str);
int				ft_strint(char *str, char c);
void			export_in_envv(t_list **envv, char *var_val);
void			export_handler(t_data *info, int index);

// export_utils.c
void			split_and_print(char *smallest);
void			sort_list(t_list *envv);
void			indexing(t_list *envv);

// unset.c
void			unset_handler(t_data *info, int index);
void			remove_in_envv(t_list **envv, char *var);
int				replace_value_in_env(char **var_val, char *var,
					t_list *tmp, t_list *curr);
void			handle_struct(t_data *info);
// echo.c
void			ft_echo(t_data *info);

// pwd.c
void			print_path(void);

// signals.c
void			handle_sigs_interactive(void);

// cd.c
void			cd(t_data *info);

//		execution
// kuba

// New exec
char			*cmd_exists_inp(char *line, char *cmd);
void			fake_here_doc(char *line);
int				real_here_doc(char *line);
int				get_real_one(t_data *info, int i);
int				get_the_real_one_out(t_data *info, int out_fd, int i);
int				put_proper_in_fd(t_data *info, int fd);
int				put_proper_out_fd(t_data *info, int out_fd);
char			*cmd_exists(t_data *info);
int				child_process_in(t_data *info, int fd, int *pipe_1);
int				child_process_out(t_data *info, int out_fd, int *pipe_1);
void			run_child(t_data *info, int fd, int out_fd, int *pipe_1);
int				fork_and_exec(t_data *info, int fd, int out_fd);
int				exec_prep_thingys(t_data *info, int fd, int out_fd);
int				exec_stuff(t_data *info);
char			*get_path(char **envv);
char			*check_for_cmd_in_path(char *path, char *command);
void			print_2d_array(char **arr, int fd);
char			**add_after_string(char **arr, char *new_el);
void			handle_child_signals(void);
int				get_the_real_one_out(t_data *info, int out_fd, int i);
int				get_real_one(t_data *info, int i);
void			fake_here_doc(char *line);
char			**convert_env_list_to_str(t_list **envv);
void			update_env(t_data *info);
int				prep_manag(t_data *info, int *fd, int *out_fd);
int				get_out(t_data *info, int i, int *out_fd);
void			write_err(t_data *info);
// Exit
void			exit_program(t_data *info);
void			end_free(char *input, t_data *info);
int				check_if_only_nums(char *str);
// Sig
void			handle_here_doc_sig_par(void);
// Env
void			print_envv(t_list **envv, int flag);
int				get_size_of_list(t_list **envv);
char			**convert_env_list_to_str(t_list **envv);
char			**add_env(char **env);
void			free_2d_array(char **arr);
void			free_all(t_data *info);
void			clear_before_ex(t_data *info, int i);
int				no_path_handling(t_data *info, int fd, int out_fd);
int				check_for_build_child_build_ins(t_data *info);
int				non_fork_buid_ins(t_data *info);
void			exit_check(t_data *info, int i);
void			manage_for_in_out(t_data *info);
t_cmd			*alloc_mem_for_info(t_cmd *cmd);
void			handle_red_p(t_data *info, char **temp, t_container *container);
void			handle_red_t(t_data *info, char **temp, t_container *container);
#endif
