/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:49:23 by moabed            #+#    #+#             */
/*   Updated: 2026/05/16 16:15:25 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executionpart.h"

static void	execute_as_is(t_exec *shell, t_cmd *node)
{
	int	err;

	if (ft_strchr(node->args[0], '/'))
	{
		execve(node->args[0], node->args, shell->envp);
		err = errno;
		perror(node->args[0]);
		free_current_cmd(&node);
		if (err == ENOENT)
			exit(127);
		else
			exit(126);
	}
}

void	execute(t_exec *shell, t_cmd *node)
{
	int		i;
	char	**path;
	char	*cmd_path;

	i = -1;
	execute_as_is(shell, node);
	path = findpath(shell->first_env_node);
	if (!path)
	{
		error_display(STDERR_FILENO, node->args[0],
			": No such file or directory", shell);
		free_current_cmd(&node);
		exit(127);
	}
	while (path[++i])
	{
		cmd_path = ft_strjoin(path[i], node->args[0]);
		execve(cmd_path, node->args, shell->envp);
		free(cmd_path);
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

static void	execute_non_builtin(t_exec *shell, t_cmd *node)
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

void    execute_one_cmd(t_exec *shell, t_cmd *node)
{
	if (!node)
		return ;
	if (preprocess_heredocs(shell, node) == -1)
		return ;
	redir_handle(node->redir, &node);
	if (node->fd_in == -1 || node->fd_out == -1)
	{
		shell->last_status = 1;
		return ;
	}
	if (!node->args || !node->args[0])
	{
		shell->last_status = 0;
		return ;
	}
	if (node->cmd_type == NONE)
		execute_non_builtin(shell, node);
	else
		exec_builtin(shell, node);
}
