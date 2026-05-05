/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 12:57:18 by moabed            #+#    #+#             */
/*   Updated: 2026/05/05 16:53:57 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executionpart.h"

void	her_int(int sig)
{
	(void)sig;
	g_sig = 130;
	ft_putchar_fd('\n', 1);
	close(STDIN_FILENO);
}
void	heredoc_signals(void)
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

int	heredoc(t_exec *shell, char *delimiter, t_cmd **node)
{
	char	*line;
	char	*expanded_line;
	int		fd[2];
	int		stdin_backup;

	if (pipe(fd) == -1)
		return (-1);
	stdin_backup = dup(STDIN_FILENO);
	heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		expanded_line = expand_value(line, shell->envp, shell->last_status);
		ft_putstr_fd(expanded_line, fd[1]);
		ft_putchar_fd('\n', fd[1]);
		free(line);
		free(expanded_line);
	}
	close(fd[1]);
	apply_fd(stdin_backup, STDIN_FILENO);
	interactive_signals();
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
