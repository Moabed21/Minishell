/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:49:23 by moabed            #+#    #+#             */
/*   Updated: 2026/05/10 16:23:43 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/executionpart.h"

void	execute_as_is(t_exec *shell, t_cmd *node)
{
	if (ft_strchr(node->args[0], '/'))
	{
		execve(node->args[0], node->args, shell->envp);
		perror(node->args[0]);
		free_current_cmd(&node);
		exit(126);
	}
}

void	execute(t_exec *shell, t_cmd *node)
{
	int		i;
	char	**path;
	char	*first_part;

	i = -1;
	execute_as_is(shell, node);
	path = findpath(shell->first_env_node);
	if (!path)
	{
		free_current_cmd(&node);
		free2d_array(shell->envp);
		exit(127);
	}
	while (path[++i])
	{
		first_part = ft_strjoin(path[i], node->args[0]);
		free(path[i]);
		path[i] = first_part;
		execve(path[i], node->args, shell->envp);
	}
	error_display(STDERR_FILENO, node->args[0], ": command not found", shell);
	free2d_array(path);
	free_current_cmd(&node);
	exit(127);
}

void	check_fds(t_cmd *node)
{
	if (node->fd_in > 2)
	{
		close(node->fd_in);
		node->fd_in = 0;
	}
	if (node->fd_out > 2)
	{
		close(node->fd_out);
		node->fd_out = 1;
	}
}

void	execute_non_builtin(t_exec *shell, t_cmd *node)
{
	ft_fork_pipe(shell, node, 1);
	if (node->fork_id == -1)
		return ;
	if (node->fork_id == 0)
	{
		default_signals();
		if (node->fd_in != 0)
			apply_fd(node->fd_in, 0);
		if (node->fd_out != 1)
			apply_fd(node->fd_out, 1);
		execute(shell, node);
	}
	ignore_signals();
	check_fds(node);
	wait_child(shell, node);
}

void	execute_one_cmd(t_exec *shell, t_cmd *node)
{
	redir_handle(shell, node->redir, &node);
	if (!node)
	{
		shell->cmds = NULL;
		shell->last_status = 1;
		return ;
	}
	if (node->cmd_type == NONE)
		execute_non_builtin(shell, node);
	else
		exec_builtin(shell, node);
}
