NAME = minishell

SRCS =	main.c \
		Libft/*.c \
		parse/input.c \
		parse/input_utils.c \
		parse/envv.c \
		parse/quotes.c \
		builtins/handler.c \
		builtins/echo.c \
		format/put_command.c\
		builtins/pwd.c\
		builtins/cd.c


all: minishell

$(NAME):
	gcc -Wall -Wextra -Werror -lreadline -ggdb3 -o $(NAME) $(SRCS)
clean:
	@rm -f minishell
fclean:
	@rm -f minishell
re: fclean all

.PHONY: all clean fclean re