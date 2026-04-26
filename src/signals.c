/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 19:23:25 by moabed            #+#    #+#             */
/*   Updated: 2026/04/11 17:19:15 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// this is the signals part

#include "../headers/execution-part.h"

void	sigint_interactive(int sig)
{
	(void)sig;
	global_sig = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_interactive(int sig)
{
	(void)sig;
	rl_redisplay();
	return ;
}

void	interactive_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_interactive;
	sigemptyset(&sa_int.sa_mask);
	// this means " dont block other signals during handler"
	sa_int.sa_flags = 0;
	// dont set SA_restart (important for readline)
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = sigquit_interactive;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	rl_catch_signals = 0; // Tell readline: "I'll handle signals myself"
}

void	default_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}
