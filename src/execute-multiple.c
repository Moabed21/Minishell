/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute-multiple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 09:54:05 by moabed            #+#    #+#             */
/*   Updated: 2026/05/05 08:55:42 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executionpart.h"

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
}

void	run_pipeline(t_exec *shell, t_cmd *node)
{
	default_signals();
	if (node->fd_in != 0)
		apply_fd(node->fd_in, 0);
	if (node->fd_out != 1)
		apply_fd(node->fd_out, 1);
	if (node->next)
		close(shell->fd[0]);
	if (node->cmd_type == NONE)
		execute(shell, node);
	else
	{
		exec_builtin(shell, node);
		exit(shell->last_status);
	}
}

void	mcc(t_exec *shell, t_cmd **cmds, int prev_fd)
{
	if ((*cmds)->next)
		ft_fork_pipe(shell, *cmds, 2);
	if ((*cmds)->fork_id == -1)
		return ;
	if ((*cmds)->redir)
		redir_handle(shell, (*cmds)->redir, cmds);
	if (!*cmds)
		return ;
	if (prev_fd != -1 && (*cmds)->fd_in == 0)
		(*cmds)->fd_in = prev_fd;
	else if (prev_fd != -1)
		close(prev_fd);
	if ((*cmds)->next && (*cmds)->fd_out == 1)
		(*cmds)->fd_out = shell->fd[1];
	else if ((*cmds)->next)
		close(shell->fd[1]);
}

void	multiple_cmds(t_exec *shell, t_cmd *cmds)
{
	int	prev_fd;

	ignore_signals();
	prev_fd = -1;
	while (cmds)
	{
		mcc(shell, &cmds, prev_fd);
		if (!cmds || cmds->fork_id == -1)
			break ;
		ft_fork_pipe(shell, cmds, 1);
		if (cmds->fork_id == -1)
			break ;
		if (cmds->fork_id == 0)
			run_pipeline(shell, cmds);
		check_fds(cmds);
		if (cmds->next)
			prev_fd = shell->fd[0];
		else
			prev_fd = -1;
		cmds = cmds->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	wait_all(shell);
}
