/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:47:51 by moabed            #+#    #+#             */
/*   Updated: 2026/05/18 15:51:57 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executionpart.h"

void	wait_all(t_exec *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmds;
	while (cmd)
	{
		if (cmd->fork_id > 0)
			wait_child(shell, cmd);
		cmd = cmd->next;
	}
	if (shell->sigquit_received)
	{
		write(2, "Quit (core dumped)\n", 19);
		shell->sigquit_received = 0;
	}
	if (shell->sigint_received)
	{
		write(1, "\n", 1);
		shell->sigint_received = 0;
	}
}

void	close_all_saved_fds(t_cmd *cmds)
{
	while (cmds)
	{
		if (cmds->fd_in > 2)
			close(cmds->fd_in);
		if (cmds->fd_out > 2)
			close(cmds->fd_out);
		cmds = cmds->next;
	}
}

void	handle_fds(t_exec *shell, t_cmd *node)
{
	if (node->fd_in > 2)
	{
		apply_fd(node->fd_in, 0);
		node->fd_in = 0;
	}
	if (node->fd_out > 2)
	{
		apply_fd(node->fd_out, 1);
		node->fd_out = 1;
	}
	if (node->next)
	{
		close(shell->fd[0]);
		if (node->fd_out != shell->fd[1])
			close(shell->fd[1]);
	}
}