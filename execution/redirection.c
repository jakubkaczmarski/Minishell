#include "../minishell.h"

char	*get_wrd(char *trimmed_line, int *i)
{
	if(trimmed_line[*i])
	{
		if(trimmed_line[*i] == '<' || trimmed_line[*i] == '>')
		{
			*i = *i + 1;
			if((trimmed_line[*i] == '<' && trimmed_line[*i + 1] == '<') || (trimmed_line[*i + 1] == '>' && trimmed_line[*i] == '>'))
			{
				*i = *i + 1;
			}
			
		}
	}
	// printf("index %d", *i);
	while(trimmed_line[*i])
	{
		if(trimmed_line[*i + 1] == '<' || trimmed_line[*i + 1] == '>' || !trimmed_line[*i + 1])
		{
			*i = *i + 1;
			return ft_substr(trimmed_line, 0,*i);
		}
		*i = *i + 1;
	}
	return NULL;
}
int Kurwa(t_el_counter *kurwa, char *line)
{
	int i = 0;
	char *trimmed_line;
	trimmed_line = ft_strtrim(line, " ");
	int index = 0;
	// int i_prev_index = 0;
	char *wrd = get_wrd(trimmed_line, &index);
	i++;
	char *temp;
	if(kurwa){}
	while(wrd)
	{
		free(wrd);
		temp = trimmed_line;
		trimmed_line = ft_substr(trimmed_line, index, ft_strlen(trimmed_line) - index);
		index = 0;
		free(temp);
		wrd = get_wrd(trimmed_line, &index);
		i++;
	}
	if(wrd)
	{}
	if(i == 0)
		return 0;
	kurwa->redirect_arr = malloc(sizeof(char**) * (i));
	kurwa->num_of_wrds = i;
	i = 0;
	index = 0;
	trimmed_line = ft_strtrim(line, " ");

	kurwa->redirect_arr[i] = get_wrd(trimmed_line, &index);
	i++;

	while(i < kurwa->num_of_wrds  )
	{
		temp = trimmed_line;
		trimmed_line = ft_substr(trimmed_line, index, ft_strlen(trimmed_line) - index);
		index = 0;
		free(temp);
		kurwa->redirect_arr[i] = get_wrd(trimmed_line, &index);
		i++;
	}
	return 0;
}
int		exec_input_redirection(char *line)
{
	if(line){}
		return 1;
}
int		exec_double_input_redirection(char *line)
{
	if(line){}
		return 1;
}

int		loop_through_redir(t_el_counter *el_counter)
{
	int i = 0;
	while(el_counter->redirect_arr[i])
	{
		if(el_counter->redirect_arr[i][0] == '<')
		{
			
			if(el_counter->redirect_arr[i][1] == '<')
			{

			}else
				exec_input_redirection(el_counter->redirect_arr[i]);
		}
		i++;
	}
	return 0;
}
int		run_redictions(t_data *info, int index)
{
	t_el_counter el_counter;
	if(!(ft_strchr(info->cmd_table[index], '<') || ft_strchr(info->cmd_table[index], '>')))
	{
		printf("Redirections are not in the string 🦖\n");
		return 0;
	}
	Kurwa(&el_counter, info->cmd_table[index]);
	loop_through_redir(&el_counter);
	int i = 0;
	while(i < el_counter.num_of_wrds - 1 )
	{
		// printf("Output %s\n", el_counter.redirect_arr[i]);
	
		free(el_counter.redirect_arr[i]);
		i++;
	}
	free(el_counter.redirect_arr);
	return 1;
}

