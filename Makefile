NAME = minishell

SRCS =	main.c \
		Libft/*.c \
		parse/input.c \


all: minishell

$(NAME):
	gcc -Wall -Wextra -Werror -lreadline -ggdb3 -o $(NAME) $(SRCS)
clean:
	@rm -f minishell
fclean:
	@rm -f minishell
re: fclean all

.PHONY: all clean fclean re