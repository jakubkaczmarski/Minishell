all: minishell

minishell:
	gcc -Wall -Wextra -Werror -o minishell main.c 
clean:
	@rm -f minishell
fclean:
	@rm -f minishell
re: fclean all

.PHONY: all clean fclean re