/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:52:30 by jtomala           #+#    #+#             */
/*   Updated: 2022/05/29 19:36:40 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	sigint_handler(int signal)
{
	if (signal)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_redisplay();
	}
}

static void	child_signal_handler(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
	else if (signal == SIGINT)
		ft_putchar_fd('\n', STDERR_FILENO);
}

void	handle_child_signals(void)
{
	signal(SIGINT, child_signal_handler);
	signal(SIGQUIT, child_signal_handler);
}

/*
Signal handler for the keyboard to controll the shell
@param SIGINT CTL+C
@param SIGQUIT CTL+\
@param SIG_IGN ignores other signals
*/
void	handle_sigs_interactive(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_here_doc_sig_par(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}
