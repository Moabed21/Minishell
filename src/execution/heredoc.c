/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 12:57:18 by moabed            #+#    #+#             */
/*   Updated: 2026/05/14 08:47:34 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executionpart.h"
#include "../../headers/parsingpart.h"

static void	her_int(int sig)
{
	(void)sig;
	g_sig = 130;
	ft_putchar_fd('\n', 1);
	close(STDIN_FILENO);
}

static void	heredoc_signals(void)
{
	struct sigaction	sa;
	struct sigaction	sa_quit;

	sa.sa_handler = her_int;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

static void	message_display(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}

static void	heredoc_loop(t_exec *shell, int fd[2], int quoted, char *delimiter)
{
	char	*line;
	char	*expanded_line;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
		{
			if (!line)
				message_display(delimiter);
			free(line);
			break ;
		}
		if (!quoted)
			expanded_line = expand_value(line, shell->first_env_node,
					shell->last_status, 0);
		else
			expanded_line = ft_strdup(line);
		ft_putstr_fd(expanded_line, fd[1]);
		ft_putchar_fd('\n', fd[1]);
		free(line);
		free(expanded_line);
	}
}

int	heredoc(t_exec *shell, char *delimiter, t_cmd **node, int quoted)
{
	int	fd[2];
	int	stdin_restore;

	if (pipe(fd) == -1)
		return (-1);
	stdin_restore = dup(STDIN_FILENO);
	heredoc_signals();
	heredoc_loop(shell, fd, quoted, delimiter);
	close(fd[1]);
	interactive_signals();
	apply_fd(stdin_restore, STDIN_FILENO);
	if (g_sig == 130)
	{
		close(fd[0]);
		free_current_cmd(node);
		return (-1);
	}
	if ((*node)->fd_in > 2)
		close((*node)->fd_in);
	(*node)->fd_in = fd[0];
	return (0);
}
