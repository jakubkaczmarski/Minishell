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


all: minishell

$(NAME):
	gcc -Wall -Wextra -Werror -lreadline -ggdb3 -o $(NAME) $(SRCS)
clean:
	@rm -f minishell
fclean:
	@rm -f minishell
re: fclean all

.PHONY: all clean fclean re