/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute-multiple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 09:54:05 by moabed            #+#    #+#             */
/*   Updated: 2026/05/19 09:55:41 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executionpart.h"

static void	run_pipeline(t_exec *shell, t_cmd *node)
{
	default_signals();
	if (node->fd_in == -1 || node->fd_out == -1)
	{
		close_all_saved_fds(shell->cmds);
		free_cmds_list(&shell->cmds);
		exit(1);
	}
	handle_fds(shell, node);
	close_all_saved_fds(shell->cmds);
	if (!node->args || !node->args[0])
	{
		free_cmds_list(&shell->cmds);
		exit(0);
	}
	if (node->cmd_type == NONE)
		execute(shell, node);
	else
	{
		exec_builtin(shell, node);
		free_cmds_list(&shell->cmds);
		exit(shell->last_status);
	}
}

static void	mcc(t_exec *shell, t_cmd **cmds, int prev_fd)
{
	if ((*cmds)->next)
	{
		ft_fork_pipe(shell, *cmds, 2);
		if ((*cmds)->fork_id == -1)
			return ;
	}
	if ((*cmds)->redir)
		redir_handle((*cmds)->redir, cmds);
	if (prev_fd != -1 && (*cmds)->fd_in == 0)
		(*cmds)->fd_in = prev_fd;
	else if (prev_fd != -1)
		close(prev_fd);
	if ((*cmds)->next && (*cmds)->fd_out == 1)
		(*cmds)->fd_out = shell->fd[1];
}

static int	manage_parent_pipes(t_exec *shell, t_cmd *cmds, int *prev_fd)
{
	if (cmds->fork_id == -1)
	{
		if (cmds->next)
			close_pipe(shell);
		return (0);
	}
	if (cmds->fork_id == 0)
		run_pipeline(shell, cmds);
	if (cmds->next)
	{
		close(shell->fd[1]);
		shell->fd[1] = -1;
	}
	if (cmds->next)
		*prev_fd = shell->fd[0];
	else if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	return (1);
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
		if (cmds->fork_id == -1)
			break ;
		ft_fork_pipe(shell, cmds, 1);
		if (!manage_parent_pipes(shell, cmds, &prev_fd))
			break ;
		cmds = cmds->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	wait_all(shell);
}
