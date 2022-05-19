NAME = minishell

SRCS =	main.c \
		Libft/*.c \
		parse/input.c \
		parse/input_utils.c \
		parse/envv.c \
		parse/quotes.c \
		parse/cmd_table.c \
		parse/cmd_table_utils.c \
		builtins/handler.c \
		builtins/echo.c \
		builtins/export.c \
		builtins/export_utils.c \
		builtins/unset.c \
		builtins/signals.c \
		builtins/pwd.c\
		builtins/cd.c\
		#execution/finding_command_path.c\
		execution/redirection.c\
		execution/allocating_for_cmd.c\
		execution/convert.c \
		execution/exec_cmd.c\
		execution/handling_cmd.c\

all: minishell

$(NAME):
	gcc -Wall -Wextra -Werror -ggdb3 -o $(NAME) $(SRCS) -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline
clean:
	@rm -f minishell
fclean:
	@rm -f minishell
re: fclean all

.PHONY: all clean fclean re