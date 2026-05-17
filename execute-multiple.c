/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute-multiple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 09:54:05 by moabed            #+#    #+#             */
/*   Updated: 2026/05/17 23:38:41 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executionpart.h"

static void	wait_all(t_exec *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmds;
	while (cmd)
	{
		if (cmd->fork_id > 0)
			wait_child(shell, cmd);
		cmd = cmd->next;
	}
	while (wait(NULL) != -1)
		;
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

static void	run_pipeline(t_exec *shell, t_cmd *node)
{
	default_signals();
	if (node->fd_in == -1 || node->fd_out == -1)
		exit(1);
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
		close(shell->fd[0]);
	close_all_saved_fds(shell->cmds);
	if (!node->args || !node->args[0])
		exit(0);
	if (node->cmd_type == NONE)
		execute(shell, node);
	else
	{
		exec_builtin(shell, node);
		exit(shell->last_status);
	}
}

static void	mcc(t_exec *shell, t_cmd **cmds, int prev_fd)
{
	if ((*cmds)->next)
		ft_fork_pipe(shell, *cmds, 2);
	if ((*cmds)->fork_id == -1)
		return ;
	if ((*cmds)->redir)
		redir_handle((*cmds)->redir, cmds);
	if (!*cmds)
		return ;
	if (prev_fd != -1 && (*cmds)->fd_in == 0)
		(*cmds)->fd_in = prev_fd;
	else if (prev_fd != -1)
		close(prev_fd);
	if ((*cmds)->next && (*cmds)->fd_out == 1)
		(*cmds)->fd_out = shell->fd[1];
}

void	multiple_cmds(t_exec *shell, t_cmd *cmds)
{
	int	prev_fd;

	if (preprocess_heredocs(shell, cmds) == -1)
		return ;
	ignore_signals();
	prev_fd = -1;
	while (cmds)
	{
		mcc(shell, &cmds, prev_fd);
		if (!cmds)
			break ;
		ft_fork_pipe(shell, cmds, 1);
		if (cmds->fork_id == -1)
			break ;
		if (cmds->fork_id == 0)
			run_pipeline(shell, cmds);
		if (cmds->next)
		{
			close(shell->fd[1]);
			if (cmds->fd_out == shell->fd[1])
				cmds->fd_out = 1;
			prev_fd = shell->fd[0];
			if (cmds->fd_in == prev_fd)
				cmds->fd_in = 0;
		}
		else
			prev_fd = -1;
		check_fds(cmds);
		cmds = cmds->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	wait_all(shell);
}
