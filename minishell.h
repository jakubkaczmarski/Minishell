/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:02:58 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/05/25 19:41:16 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>


//ls > something | wc -c 
typedef struct s_cmd {
	char	**in;			//< something.txt
							//<<something.txt
	char	**out;			//> something.txt
							//>>something.txt
	char	**cmd;		//ls[0]wc-l[1]

	char	*command_path; //full cmd_path
	char	*gen_path;	//partial path to cmd
}				t_cmd;

//main-struct
typedef struct s_data {
	char	**cmd_table;
	t_list	*envv;
	t_cmd	*cmd; //call it in an array
	int		amount_cmd;
	char	*path;
	int			index;
	int			pid;
	int			forker;
	char	**env;
	char	**command_and_param;
	int			ret_val;
}				t_data;

typedef struct s_count_el
{
	char **redirect_arr;
	t_cmd *cmd_arr;
	int red_num_in;
	int	red_num_out;
	int n_cmd_flags;
	int	num_of_wrds;
	int	num_of_cmds;
	int	ida_cmd_flags;
	int fd_input;
	int fd_output;
	int here_doc_thingy;
	char *magic_here_doc_word;
} t_el_counter;

//main.c
int		input_error();
void	print_envv(t_list *envv, int flag);

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
int replace_line(t_data *info, int index, char c);
int	crop_redir(t_data *info);
//struct.c
void handle_struct(t_data *info);

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
int		flag_check(char *input, int counter);

//			builtins
//execution_handler.c
int		builtin_handler(t_data *info);

//export.c
int		ft_isvalid(char *str);
int		ft_strint(char *str, char c);
void	export_in_envv(t_list **envv, char *var_val);
void	export_handler(t_data *info, int index);

//export_utils.c
void	split_and_print(char *smallest);
void	sort_list(t_list *envv);
void indexing(t_list *envv);

//unset.c
void	unset_handler(t_data *info, int index);
void	remove_in_envv(t_list **envv, char *var);
int		replace_value_in_env(char **var_val, char *var, t_list *tmp, t_list *curr);
void	handle_struct(t_data *info);
//echo.c
void	ft_echo(t_data *info);

//pwd.c
void	print_path(void);

//signals.c
void	handle_sigs_interactive(void);

//cd.c
void	cd(t_data *info);

//		execution
//kuba
char	**get_env_arr(t_data *info);
void	manage_exec(t_data *info, char **env);
int		split_path_to_exec( t_data *info, int forker, int i);
char	*check_for_cmd_in_path(char *path, char *command);
char	*get_path(char **envv);
char	**command_and_param_from_line(char *line);
void	execute_single_command(t_data *info, int index, int forker, int i);
int		piping(t_data *info,  int index);
int		find_len_first_command(t_data *info, int index);
int		run_redictions(t_data *info, int index, char ** env);
int		get_num_to_alloc(t_el_counter *el_count, t_data *info, int index);
int		alloc_mem_for_words(t_el_counter *el_count, t_data *info, int index);
void	manage_input_red(char *line);
int		Kurwa(t_el_counter *kurwa, char *line);
int		exec_input_red(t_el_counter *el_counter);
int		exec_output_red(t_el_counter *el_counter);
int		loop_through_redir(t_el_counter *el_counter);
int		check_for_buildins(char *line, char **env);
int		get_here_doc(t_el_counter *el_counter);
int		manage_here_doc(t_el_counter *el_counter, int index);
int		check_if_only_red(char *cmd);
char	*exec_cmd(t_data *info, int forker, int index, char **splitted_path);
int					free_exec(char **splitted_path, char *full_cmd_path);
char				**convert(t_list *envv);
void				loop_through_red_right(t_el_counter *el_counter, int i);
void				loop_through_red_left(t_el_counter *el_counter, int i);
void				format_line_to_exec(t_el_counter *el_counter, char *trimmed_line);
int					exec_cmd_and_close_fds(t_el_counter *el_counter, char  **env);
char			*get_cmd(t_el_counter *counter);

//New exec
void    fake_here_doc(char *line);
int    real_here_doc(char *line);
int get_real_one(t_data *info, int i);
int get_the_real_one_out(t_data *info, int out_fd, int i);
int put_proper_in_fd(t_data *info, int fd);
int put_proper_out_fd(t_data *info, int out_fd);
char *cmd_exists(t_data *info);
int child_process_in(t_data *info, int fd, int *pipe_1);
int child_process_out(t_data *info, int out_fd, int *pipe_1);
void run_child(t_data *info,int  fd,int out_fd,int *pipe_1);
int fork_and_exec(t_data *info,int fd, int out_fd);
int exec_prep_thingys(t_data *info,int fd, int out_fd);
int exec_stuff(t_data *info);
char *get_path(char **envv);
char *check_for_cmd_in_path(char *path, char *command);
void    print_2d_array(char    **arr, int fd);
char **add_after_string(char **arr, char *new_el);
#endif
